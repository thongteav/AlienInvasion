#pragma once

#ifndef __GREEN_BOSS_H__
#define __GREEN_BOSS_H__

// Local includes:
#include "Boss.h"
#include "BackBuffer.h"

class GreenBoss : public Boss
{
	// Member Methods:
public:
	GreenBoss();
	GreenBoss(float x, float y, int width, int height, int m_health);

	bool Initialise(BackBuffer& backBuffer);

	void Attack(float deltaTime);
	
protected:

private:

	// Member Fields:
public:

protected:

private:
	
	
	
};

#endif // !__GREEN_BOSS_H__
