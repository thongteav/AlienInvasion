// This include:
#include "Ball.h"

// Local includes:
#include "Entity.h"
#include "Game.h"
#include "LogManager.h"

// Library includes:
#include <cmath>
#include <string>

const double INITIAL_ANGLE = 90;
const double ANGLE_RANGE = 60;

#define PI 3.14159265

Ball::Ball ()
: Entity()
{
	SetAngle(INITIAL_ANGLE);
}

Ball::Ball(float x, float y, int width, int height)
: Entity(x, y, width, height)
{
	SetAngle(INITIAL_ANGLE);
}

void
Ball::Process(float deltaTime)
{
	UpdatePositionWithAngle(deltaTime);
	CheckBoundary();
}

void
Ball::Draw(BackBuffer& backBuffer)
{
	Entity::Draw(backBuffer);
}

bool
Ball::AABBCollision(Entity& e)
{
	bool collided = false;
	float x, y, width, height;

	if (m_velocityX > 0)
	{
		x = m_x;
		width = m_velocityX + static_cast<float>(m_width);
	}
	else
	{
		x = m_x + m_velocityX;
		width = static_cast<float>(m_width) - m_velocityX;
	}

	if (m_velocityY > 0)
	{
		y = m_y;
		height = m_velocityY + static_cast<float>(m_height);
	}
	else
	{
		y = m_y + m_velocityY;
		height = static_cast<float>(m_height) - m_velocityY;
	}

	float eX = e.GetPositionX();
	float eY = e.GetPositionY();

	bool xOverlapped = (x < eX + e.GetWidth()) && (x + width > eX);
	bool yOverlapped = (y + height > eY) && (y < eY + e.GetHeight());

	if (xOverlapped && yOverlapped)
	{
		collided = true;
	}

	return (collided);
}

bool
Ball::IsCollidingWith(Entity& e, float deltaTime)
{
	bool collided = false;

	if (AABBCollision(e))
	{
		float normalX, normalY;
		float collisionTime = SweptAABBCollision(e, normalX, normalY, deltaTime);

		if (collisionTime < (1.0f))
		{
			double rad = static_cast<double>(m_angle * PI / 180.0);
			m_x += m_velocityX * collisionTime * static_cast<float>(cos(rad)) * deltaTime;
			m_y += m_velocityY * collisionTime * static_cast<float>(cos(rad)) * deltaTime;

			/*float remainingTime =  deltaTime * (1 - collisionTime);

			m_velocityX *= remainingTime;
			m_velocityY *= remainingTime;*/

			if (abs(normalX) > 0.0001f)
			{
				m_velocityX = -m_velocityX;
			}

			if (abs(normalY) > 0.0001f)
			{
				m_velocityY = -m_velocityY;
			}

			LogManager::GetInstance().Log("collided");

			collided = true;
		}
		else
		{
			collided = false;
		}
	}	

	return collided;
}

void
Ball::CheckBoundary()
{
	if (m_x < 0)
	{
		m_x = 0;
		m_velocityX = -m_velocityX;
	}
	else if (m_x + m_width > Game::WIDTH)
	{
		m_x = static_cast<float>(Game::WIDTH - m_width);
		m_velocityX = -m_velocityX;
	}

	if (m_y < 0)
	{
		m_y = 0;
		m_velocityY = -m_velocityY;
	}

	if (m_y > Game::HEIGHT + m_height)
	{
		m_dead = true;
		m_velocityX = 0;
		m_velocityY = 0;
	}
}

void
Ball::BounceOffPaddle(Entity& e)
{
	float diff = m_x + m_width - e.GetPositionX();
	double angleDif = static_cast<double>(Lerp(45, -45, static_cast<float>(diff / e.GetWidth())));
	
	m_angle = INITIAL_ANGLE + angleDif;
	m_velocityY = -abs(m_velocityY);

	if (angleDif > 0)
	{
		m_velocityX = -abs(m_velocityX);
		m_angle = INITIAL_ANGLE - angleDif;
	}
	else if (angleDif < 0)
	{
		m_velocityX = abs(m_velocityX);
		m_angle = INITIAL_ANGLE + angleDif;
	}
	else
	{
		m_velocityX = 0;
		m_angle = INITIAL_ANGLE + angleDif;
	}

	std::string msg = "Angle: " + std::to_string(m_angle);
	LogManager::GetInstance().Log(msg.c_str());
}

void
Ball::BounceOff(Entity& e)
{
	if (m_x > e.GetPositionX() && m_x < e.GetPositionX() + static_cast<float>(e.GetWidth()))
	{
		m_velocityY = -m_velocityY;
	}
	else if (m_y > e.GetPositionY() && m_y < e.GetPositionY() + static_cast<float>(e.GetHeight()))
	{
		m_velocityX = -m_velocityX;
	}
}

void
Ball::MoveAngleClockwise()
{
	if (m_angle < 155)
	{
		++m_angle;
	}
}

void
Ball::MoveAngleAntiClockwise()
{
	if (m_angle > 25)
	{
		--m_angle;
	}
}

void
Ball::Reset()
{
	m_x = static_cast<float>(Game::WIDTH / 2 - m_width / 2);
	m_y = static_cast<float>((Game::HEIGHT / 8 * 7) - m_height);
	m_angle = INITIAL_ANGLE;
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
	m_dead = false;
}
