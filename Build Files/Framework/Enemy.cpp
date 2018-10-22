// This include:
#include "Enemy.h"
#include "SpriteSheet.h"

// Local includes:

// Library includes:
#include <cassert>
#include <cstdlib>

Enemy::Enemy()
: Entity()
, m_pSpriteSheet(0)
, m_status(Status::STAND)
{
	m_colour = static_cast<Colour>(rand() % Colour::COLOUR_SIZE);
}

Enemy::Enemy(float x, float y, int width, int height)
: Entity(x, y, width, height)
, m_pSpriteSheet(0)
, m_status(Status::STAND)
{
	m_colour = static_cast<Colour>(rand() % Colour::COLOUR_SIZE);
}

Enemy::~Enemy()
{
	Entity::~Entity();

	delete m_pSpriteSheet;
	m_pSpriteSheet = 0;
}

bool
Enemy::Initialise(SpriteSheet* spritesheet)
{
	assert(spritesheet);
	m_pSpriteSheet = spritesheet;

	return (true);
}

void
Enemy::Process(float deltaTime)
{
	if (m_status != Status::DEAD)
	{
		m_pSpriteSheet->Process(deltaTime);
	}
	else
	{
		m_dead = true;
	}
}

void
Enemy::Draw(BackBuffer& backBuffer)
{
	assert(m_pSpriteSheet);

	if (m_status != Status::DEAD)
	{
		m_pSpriteSheet->SetX(static_cast<int>(m_x));
		m_pSpriteSheet->SetY(static_cast<int>(m_y));
		m_pSpriteSheet->Draw(backBuffer, m_colour, m_status, m_width, m_height);
	}	
}

void
Enemy::NextStatus()
{
	m_status = static_cast<Status>((m_status + 1) % Status::STATUS_MODES);
}

void
Enemy::Revive()
{
	m_status = Status::STAND;
	m_dead = false;
}

Enemy::Status
Enemy::GetStatus()
{
	return (m_status);
}