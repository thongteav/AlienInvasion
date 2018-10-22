#pragma once

#ifndef __BOSS_H__
#define __BOSS_H__

// Local includes:
#include "Entity.h"
#include "Sprite.h"
#include "Ball.h"
#include "Laser.h"
#include "Paddle.h"

class Boss : public Entity
{
public:
	enum State {
		MOVE,
		SIGNAL,
		ATTACK
	};

	// Member Methods:
public:
	Boss();
	Boss(float x, float y, int width, int height, int m_health);
	~Boss();

	virtual bool Initialise(BackBuffer& backBuffer) = 0;

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void ProcessHealth();

	virtual void Move(float deltaTime);
	virtual void Signal(float deltaTime);
	virtual void Attack(float deltaTime);

	virtual void DrawSignal(BackBuffer& backBuffer);
	virtual void DrawAttack(BackBuffer& backBuffer);
	virtual void DrawHealthBar(BackBuffer& backBuffer);

	void LoseHealth();

	Laser* GetLaser();
	void Revive();
	
	bool IsDead();

	const char* GetString();
	void SetString(const char* string);

	void SetInitialAttackPosition();
protected:

private:


	// Member Fields:
public:

protected:
	float m_timeEllapsed;
	float m_maxMoveTime;
	float m_maxSignalTime;
	float m_maxAttackTime;

	int m_health;
	int m_maxHealth;
	int m_healthBarLength;

	Sprite* m_pSignalSprite;
	Sprite* m_pHealthBarSprite;

	State m_currentState;

	Laser* m_pLaser;
	const char* m_fragmentString;

private:
	
};

#endif // !__BOSS_H__
