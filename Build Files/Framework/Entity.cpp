// COMP710 GP 2D Framework 2018

// This include:
#include "Entity.h"

// Local includes:
#include "Sprite.h"
#include "BackBuffer.h"
#include "Game.h"
#include "LogManager.h"

// Library includes:
#include <cassert>
#include <limits>
#include <algorithm>

static const double PI = 3.141592654;

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_width(0)
, m_height(0)
, m_dead(false)
{

}

Entity::Entity(float x, float y, int width, int height)
: m_pSprite(0)
, m_x(x)
, m_y(y)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_width(width)
, m_height(height)
, m_dead(false)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void
Entity::Process(float deltaTime)
{
	UpdatePosition(deltaTime);
	CheckBoundary();
}

void
Entity::UpdatePosition(float deltaTime)
{
	m_x = m_x + m_velocityX * deltaTime;
	m_y = m_y + m_velocityY * deltaTime;
}

void
Entity::UpdatePositionWithAngle(float deltaTime)
{
	double rad = static_cast<double>(m_angle * PI / 180.0);
	m_x = m_x + m_velocityX * deltaTime * static_cast<float>(cos(rad));
	m_y = m_y + m_velocityY * deltaTime * static_cast<float>(sin(rad));
}

void
Entity::CheckBoundary()
{
	if (m_x < 0)
	{
		m_x = 0;
	}
	else if (m_x + m_width > Game::WIDTH)
	{
		m_x = static_cast<float>(Game::WIDTH - m_width);
	}
}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
}

void
Entity::DrawInDimension(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer, m_width, m_height);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	bool collided = AABBCollision(e);
	
	return (collided);
}

bool
Entity::AABBCollision(Entity& e)
{
	bool collided = false;

	if (!m_dead)
	{
		// AABB collision detection
		float eX = e.GetPositionX();
		float eY = e.GetPositionY();

		bool xOverlapped = (m_x < eX + e.GetWidth()) && (m_x + m_width > eX);
		bool yOverlapped = (m_y + m_height > eY) && (m_y < eY + e.GetHeight());

		if (xOverlapped && yOverlapped)
		{
			LogManager::GetInstance().Log("Collided");
			collided = true;
		}
	}	

	return (collided);
}

float 
Entity::SweptAABBCollision(Entity& e, float& normalX, float& normalY, float deltaTime)
{
	float xEntryDist, yEntryDist; // distance between the two closer x's 
	float xExitDist, yExitDist;   // distance between the two furtheset x's

	float myRightX = static_cast<float>(m_x + m_width);
	float eRightX = static_cast<float>(e.GetPositionX() + e.GetWidth());
	
	float myBottomY = static_cast<float>(m_y + m_height);
	float eBottomY = static_cast<float>(e.GetPositionY() + e.GetHeight());

	if (m_velocityX > 0.0f) // this entity is moving in right direction
	{
		xEntryDist = (e.GetPositionX() - myRightX);
		xExitDist = (eRightX - m_x);
	}
	else
	{
		xEntryDist = (eRightX - m_x);
		xExitDist = (e.GetPositionX() - myRightX);
	}

	if (m_velocityY > 0.0f) // if the ball is moving down
	{
		yEntryDist = e.GetPositionY() - myBottomY;
		yExitDist = eBottomY - m_y;
	}
	else
	{
		yEntryDist = eBottomY - m_y;
		yExitDist = e.GetPositionY() - myBottomY;
	}

	float xEntryTime, yEntryTime; // time taken to entry location
	float xExitTime, yExitTime;   // time taken to exit location

	if (m_velocityX == 0.0f) // to prevent dividing by 0
	{
		xEntryTime = -std::numeric_limits<float>::infinity();
		xExitTime = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntryTime = xEntryDist / (m_velocityX * deltaTime);
		xExitTime = xEntryDist / (m_velocityX * deltaTime);
	}

	if (m_velocityY == 0.0f) // to prevent dividing by 0
	{
		yEntryTime = -std::numeric_limits<float>::infinity();
		yExitTime = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntryTime = yEntryDist / (m_velocityY * deltaTime);
		yExitTime = yExitDist / (m_velocityY * deltaTime);
	}

	// the earliest or latest time of collision
	float entryTime = std::max(xEntryTime, yEntryTime);
	float exitTime = std::max(xExitTime, yExitTime);

	// no collision
	if (entryTime > exitTime || (xEntryTime < 0.0f && yEntryTime < 0.0f) || xEntryTime > (1.0f) || yEntryTime > (1.0f))
	{
		normalX = 0.0f;
		normalY = 0.0f;
		
		entryTime = 1.0f;
	}
	else // there is a collision
	{
		if (xEntryTime > yEntryTime)
		{
			if (xEntryDist < 0.0f) 
			{
				normalX = 1.0f;
				normalY = 0.0f; // right
			}
			else 
			{
				normalX = -1.0f;
				normalY = 0.0f; // left
			}
		}
		else
		{
			if (yEntryDist < 0.0f)  
			{
				normalX = 0.0f;
				normalY = 1.0f; // top
			}
			else 
			{
				normalX = 0.0f;
				normalY = -1.0f; // bottom
			}
		}
	}

	return entryTime;
}

bool
Entity::IsMoving()
{
	return ((m_velocityX != 0) || (m_velocityY != 0));
}

void
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool
Entity::IsDead() const
{
	return m_dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float
Entity::GetPositionX() const
{
	return (m_x);
}

float
Entity::GetPositionY() const
{
	return (m_y);
}

float
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

int
Entity::GetHeight()
{
	return (m_height);
}

int
Entity::GetWidth()
{
	return (m_width);
}

void
Entity::SetHeight(int height)
{
	m_height = height;
}

void
Entity::SetWidth(int width)
{
	m_width = width;
}


void
Entity::SetAngle(double angle)
{
	m_angle = angle;
}

double
Entity::GetAngle() const
{
	return (m_angle);
}

void
Entity::MoveAngleClockwise()
{
	++m_angle;
}

void
Entity::MoveAngleAntiClockwise()
{
	--m_angle;
}

float
Entity::Lerp(float initial, float final, float diff)
{
	return (1 - diff) * initial + diff * final;
}

double
Entity::ToRadian(float degree)
{
	double rad;
	rad = degree * PI / 180;

	return rad;
}
