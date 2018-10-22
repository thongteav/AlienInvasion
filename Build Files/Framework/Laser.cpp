// This include:
#include "Laser.h"
#include "LogManager.h"

Laser::Laser()
: Entity()
{

}

Laser::Laser(float x, float y, int width, int height)
: Entity(x, y, width, height)
, m_initX(x)
, m_initY(y)
{
	
}

void
Laser::Process(float deltaTime)
{
	Entity::UpdatePosition(deltaTime);
}

void
Laser::Draw(BackBuffer& backBuffer)
{
	Entity::DrawInDimension(backBuffer);
}

void
Laser::ResetToInitialPosition()
{
	m_x = m_initX;
	m_y = m_initY;
}

void
Laser::SetInitialPosition(float x, float y)
{
	m_initX = x;
	m_initY = y;
}

void
Laser::SetInitialPositionX(float x)
{
	m_initX = x;
}

void
Laser::SetInitialPositionY(float y)
{
	m_initY = y;
}

float
Laser::GetInitialPositionX()
{
	return (m_initX);
}

float
Laser::GetInitialPositionY()
{
	return (m_initY);
}