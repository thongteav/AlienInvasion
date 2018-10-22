#pragma once

#ifndef __BALL_TRAIL_H__
#define __BALL_TRAIL_H__

#include "Entity.h"

class Ball;

class BallTrail : public Entity
{
	// Member Functions
public:
	BallTrail();
	BallTrail(float x, float y, int width, int height);
	BallTrail(float x, float y, int width, int height, float radius);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void UpdatePositionWithAngle(float deltaTime);

protected:

private:

	// Member Fields
public:

protected:

private:
	float m_radius;
	float m_originX;
	float m_originY;

};

#endif // !__BALL_TRAIL_H__

