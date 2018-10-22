// This includes:
#include "PowerUp.h"
#include "Game.h"

PowerUp::PowerUp()
: Entity()
{

}

PowerUp::PowerUp(float x, float y, int width, int height)
: Entity(x, y, width, height)
{

}

void
PowerUp::Draw(BackBuffer& backBuffer)
{
	Entity::DrawInDimension(backBuffer);
}

void
PowerUp::CheckBoundary()
{
	if (m_y > Game::HEIGHT + m_height)
	{
		m_dead = true;
	}
}