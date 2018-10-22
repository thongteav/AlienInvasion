#pragma once

#ifndef __EFFECT_H__
#define __EFFECT_H__

// Local includes:
#include "Entity.h"

class Effect : public Entity
{
	// Member Functions
public:
	Effect();
	Effect(float x, float y, int width, int height);
	Effect(float x, float y, int width, int height, float maxAge);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void UpdateAge(float deltaTime);
	void Restart();

	bool IsCollidingWith(Entity& e);

protected:

private:

	// Member Fields
public:

protected:
	float m_age;
	float m_maxAge;

private:
};

#endif // !__EFFECT_H__
