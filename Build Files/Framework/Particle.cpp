// This include:
#include "Particle.h"

// Local includes:
#include "Game.h"

// Library includes:
#include <cstdlib>

Particle::Particle()
: Entity::Entity()
{

}

Particle::Particle(float x, float y, int width, int height)
: Entity::Entity(x, y, width, height)
{
	
}

Particle::~Particle()
{
	Entity::~Entity();
}

void
Particle::Process(float deltaTime)
{
	Entity::UpdatePosition(deltaTime);


	// Recycle the particle
	if (m_y > Game::HEIGHT + m_height)
	{
		m_y = static_cast<float>(-(rand() % 50));
		m_x = static_cast<float>(rand() % (Game::WIDTH - m_width));
	}
}