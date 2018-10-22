// This include:
#include "Effect.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"

// Library includes:
#include <cassert>

Effect::Effect()
: Entity()
, m_age(0)
, m_maxAge(0)
{

}

Effect::Effect(float x, float y, int width, int height)
: Entity(x, y, width, height)
, m_age(0)
, m_maxAge(0)
{

}

Effect::Effect(float x, float y, int width, int height, float maxAge)
: Entity(x, y, width, height)
, m_age(0)
, m_maxAge(maxAge)
{

}

void
Effect::Process(float deltaTime)
{
	if (!m_dead)
	{
		UpdateAge(deltaTime);
	}
}

void
Effect::UpdateAge(float deltaTime)
{
	if (!m_dead)
	{
		if (m_age < m_maxAge)
		{
			m_age += deltaTime;
		}
		else
		{
			m_dead = true;
		}
	}
}

void
Effect::Draw(BackBuffer& backBuffer)
{
	if (!m_dead)
	{
		Entity::Draw(backBuffer);
	}
}

bool
Effect::IsCollidingWith(Entity& e)
{
	bool collided = false;

	if (!m_dead)
	{
		collided = Entity::IsCollidingWith(e);
	}

	return (collided);
}

void
Effect::Restart()
{
	m_dead = false;
	m_age = 0;
}