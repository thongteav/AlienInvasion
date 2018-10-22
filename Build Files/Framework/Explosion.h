#pragma once

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

// Local includes:
#include "Entity.h"
#include "AnimatedSprite.h"

class Explosion : public Entity
{
	// Member Methods:
public:
	Explosion();
	Explosion(float x, float y, int width, int height);
	~Explosion();

	bool Initialise(AnimatedSprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	// Member Fields:
public:

protected:

private:
	AnimatedSprite * m_pAnimatedSprite;

};

#endif // !__EXPLOSION_H__

