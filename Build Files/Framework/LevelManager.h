#pragma once

#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

// Local includes:
#include "Level.h"
#include "BackBuffer.h"
#include "Paddle.h"
#include "ParticleEmitter.h"

class LevelManager
{
	// Member Methods:
public:
	LevelManager();
	~LevelManager();

	bool Initialise(BackBuffer& backBuffer);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void DeleteLevel();

	void NextLevel();
	void SetLevel(int level);
	void StartLevel();
	void RestartLevel();

	bool IsLevelCompleted();
	bool IsBossAttackHitPaddle(Paddle& paddle);
	bool IsBossHitByBall(Ball& ball, float deltaTime);
	bool IsEnemyHitByBall(Ball& ball, float deltaTime);
	bool IsBlockHitByBall(Ball& ball, float deltaTime);

	ParticleEmitter* GetParticleEmitter();
	Level* GetLevel();

protected:

private:
	void StartLevel1();
	void StartLevel2();
	void StartLevel3();
	void StartLevel4();
	void StartLevel5();
	void StartLevel6();
	void StartLevel7();
	void StartLevel8();

	// Member Fields:
public:

protected:

private:
	int m_currentLevel;

	Level* m_pLevel;
	BackBuffer* m_pBackBuffer;
	ParticleEmitter* m_pParticleEmitter;
};

#endif // !__LEVEL_MANAGER_H__

