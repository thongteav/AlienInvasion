#pragma once

#ifndef __EXPLOSION_PARTICLE_H__
#define __EXPLOSION_PARTICLE_H__

#include "Entity.h"

class ExplosionParticle : public Entity
{
	// Member Methods:
public:
	ExplosionParticle();
	ExplosionParticle(float x, float y, int width, int height);
	~ExplosionParticle();

	void Process(float deltaTime);
	void UpdateAge(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetAngle(float angle);
	void SetMaxAge(float age);

protected:

private:

	// Member Fields:
public:

protected:
	float m_angle;
	float m_age;
	float m_maxAge;

private:

};

#endif // !__EXPLOSION_PARTICLE_H__

