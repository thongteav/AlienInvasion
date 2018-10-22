#pragma once

#ifndef __PADDLE_H__
#define __PADDLE_H__

// Local includes:
#include "Entity.h"
#include "BackBuffer.h"
#include "Dizzy.h"

class Paddle : public Entity
{
public:

	// Member Methods:
public:
	Paddle();
	Paddle(float x, float y, int width, int height);
	~Paddle();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SpawnDizzy(BackBuffer& backBuffer);
	void SetDizzy(bool dizzy);

protected:

private:

	// Member Frields:
public:

protected:

private:
	bool m_dizzy;
	Dizzy* m_pDizzy;

	float m_totalEllapsedTime;
};

#endif // !__PADDLE_H__
