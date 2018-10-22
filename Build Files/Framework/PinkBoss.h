#pragma once

#ifndef __PINK_BOSS_H__
#define __PINK_BOSS_H__

// Local includes:
#include "Boss.h"
#include "BackBuffer.h"

// Library includes:
#include <vector>

class PinkBoss : public Boss
{
	// Member Methods:
public:
	PinkBoss();
	PinkBoss(float x, float y, int width, int height, int m_health);

	bool Initialise(BackBuffer& backBuffer);

	void Attack(float deltaTime);
	void Signal(float deltaTime);

	void DrawAttack(BackBuffer& backBuffer);

	void GetInitAttackPosition();
	void GetFinalAttackPosition();

	void ResetLaserPosition();

protected:

private:

	// Member Fields:
public:

protected:
	float m_attackInitX;
	float m_attackInitY;
	float m_attackFinalX;
	float m_attackFinalY;


private:

};

#endif // !__PINK_BOSS_H__
