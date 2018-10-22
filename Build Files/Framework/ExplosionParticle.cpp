// This include:
#include "ExplosionParticle.h"
#include "Sprite.h"

// Library includes:
#include <cmath>

ExplosionParticle::ExplosionParticle()
: Entity()
, m_age(0)
, m_angle(0)
, m_maxAge(0)
{

}

ExplosionParticle::ExplosionParticle(float x, float y, int height, int width)
: Entity(x, y, width, height)
, m_age(0)
, m_angle(0)
, m_maxAge(1.0f)
{

}

ExplosionParticle::~ExplosionParticle()
{
	Entity::~Entity();
}

void
ExplosionParticle::Process(float deltaTime)
{
	double rad = ToRadian(m_angle);
	m_x = m_x + static_cast<float>(std::cos(rad)) * m_velocityX * deltaTime;
	m_y = m_y + static_cast<float>(std::sin(rad)) * m_velocityY * deltaTime;
	
	UpdateAge(deltaTime);
}

void
ExplosionParticle::UpdateAge(float deltaTime)
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

void
ExplosionParticle::Draw(BackBuffer& backBuffer)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	m_pSprite->DrawRotate(backBuffer);
}

void
ExplosionParticle::SetAngle(float angle)
{
	m_angle = angle;
}

void
ExplosionParticle::SetMaxAge(float age)
{
	m_maxAge = age;
}

