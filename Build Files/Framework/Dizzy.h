#pragma once

#ifndef __DIZZY_H__
#define __DIZZY_H__

#include "Entity.h"
#include "AnimatedSprite.h"

class Dizzy : public Entity
{
	// Member Methods:
public:
	Dizzy();
	Dizzy(float x, float y, int width, int height);
	~Dizzy();

	bool Initialise(AnimatedSprite* sprite);
	
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetPosition(float x, float y);
	void AddFrames(int width, int frameCounts, float frameSpeed);

	void StartAnimating();

protected:

private:

	// Member Fields:
public:
	
protected:

private:
	AnimatedSprite * m_pAnimatedSprite;
};

#endif // !__DIZZY_H__
