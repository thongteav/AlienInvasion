// This include:
#include "BallTrail.h"

// Library includes:
#include <cmath>

#define PI 3.14159265

BallTrail::BallTrail()
: Entity()
, m_radius(0)
, m_originX(0)
, m_originY(0)
{

}

BallTrail::BallTrail(float x, float y, int width, int height)
: Entity(x, y, width, height)
, m_radius(0)
, m_originX(x)
, m_originY(y)
{
	
}

BallTrail::BallTrail(float x, float y, int width, int height, float radius)
: Entity(x, y, width, height)
, m_radius(radius)
, m_originX(x)
, m_originY(y)
{

}

void
BallTrail::Process(float deltaTime)
{
	UpdatePositionWithAngle(deltaTime);
}

void
BallTrail::Draw(BackBuffer& backBuffer)
{
	Entity::DrawInDimension(backBuffer);
}

void
BallTrail::UpdatePositionWithAngle(float deltaTime)
{
	double rad = static_cast<double>((180 - m_angle) * PI / 180.0);
	m_x = m_originX + m_radius * static_cast<float>(cos(rad));
	m_y = m_originY + m_radius * static_cast<float>(sin(rad));
}