// This include:
#include "Explosion.h"

// Library includes:
#include <cassert>

Explosion::Explosion()
: Entity()
{

}

Explosion::Explosion(float x, float y, int width, int height)
: Entity(x, y, width, height)
{

}

Explosion::~Explosion()
{
	Entity::~Entity();

	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

bool
Explosion::Initialise(AnimatedSprite* sprite)
{
	assert(sprite);
	m_pAnimatedSprite = sprite;

	return (true);
}

void
Explosion::Process(float deltaTime)
{
	if (m_pAnimatedSprite)
	{
		m_pAnimatedSprite->Process(deltaTime);

		if (m_pAnimatedSprite->IsPaused())
		{
			m_dead = true;
		}
	}
}

void
Explosion::Draw(BackBuffer& backBuffer)
{
	m_pAnimatedSprite->Draw(backBuffer, m_width);
}