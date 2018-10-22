#pragma once

#ifndef __LASER_H__
#define __LASER_H__

// Local includes:
#include "Entity.h"

class Laser : public Entity
{
	// Member Methods:
public:
	Laser();
	Laser(float x, float y, int width, int height);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetInitialPosition(float x, float y);
	void SetInitialPositionX(float x);
	void SetInitialPositionY(float y);

	float GetInitialPositionX();
	float GetInitialPositionY();

	void ResetToInitialPosition();

protected:

private:

	// Member Fields:
public:

protected:

private:
	float m_initX;
	float m_initY;

};

#endif // !__RING_H__

