#pragma once

#ifndef __BALL_H__
#define __BALL_H__

// Local includes:
#include "Entity.h"
#include "BallTrail.h"

// Library includes:
#include <vector>

class Ball : public Entity
{
	// Member Methods:
public:
	Ball();
	Ball(float x, float y, int width, int height);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void UpdatePosition(float deltaTime);
	bool IsCollidingWith(Entity& e, float deltaTime);
	bool AABBCollision(Entity& e);

	void CheckBoundary();
	void BounceOffPaddle(Entity& e);
	void BounceOff(Entity& e);

	void MoveAngleClockwise();
	void MoveAngleAntiClockwise();

	void Reset();

protected:

private:

	// Member Fields:
public:

protected:

private:
	
};
#endif // !__BALL_H__
