#pragma once

#ifndef __LEVEL_H__
#define __LEVEL_H__

// Local includes:
#include "Block.h"
#include "Enemy.h"
#include "Boss.h"
#include "PinkBoss.h"
#include "GreenBoss.h"
#include "BackBuffer.h"
#include "Paddle.h"
#include "Explosion.h"
#include "ParticleEmitter.h"

// Library includes:
#include <vector>

class Level
{
	// Member Methods:
public:
	Level();
	~Level();

	bool Initialise(BackBuffer& backBuffer, ParticleEmitter& particleEmitter);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void ProcessBlocks(float deltaTime);
	void ProcessEnemies(float deltaTime);
	void ProcessBoss(float deltaTime);
	void ProcessExplosions(float deltaTime);

	void DrawBlocks(BackBuffer& backBuffer);
	void DrawEnemies(BackBuffer& backBuffer);
	void DrawBoss(BackBuffer& backBuffer);
	void DrawExplosions(BackBuffer& backBuffer);

	void SpawnBlock(float x, float y);
	void SpawnEnemy(float x, float y);
	void SpawnGreenBoss(float x, float y, int health);
	void SpawnPinkBoss(float x, float y, int health);

	void SpawnExplosion(const char* path, float x, float y, int frameCount, float frameSpeed, int explosionSize);

	void DeleteBlocks();
	void DeleteEnemies();
	void DeleteExplosions();
	void DeleteBoss();

	void RestartLevel();

	void ReviveBlocks();
	void ReviveEnemies();
	void ReviveBoss();

	bool IsLevelCompleted();
	bool IsBossDead();
	bool AreBlocksDead();
	bool AreEnemiesDead();

	bool IsBossAttackHitPaddle(Paddle& paddle);
	bool IsBossHitByBall(Ball& ball, float deltaTime);
	bool IsEnemyHitByBall(Ball& ball, float deltaTime);
	bool IsBlockHitByBall(Ball& ball, float deltaTime);

	void ToggleEnemyDisable();
	void ToggleBlockDisable();
	void ToggleBossDisable();

	bool IsEnemyDisable();
	bool IsBlockDisable();
	bool IsBossDisable();

protected:

private:

	// Member Fields:
public:

protected:
	std::vector<Block*> m_pBlocks;
	std::vector<Enemy*> m_pEnemies;
	std::vector<Explosion*> m_pExplosions;
	Boss* m_pBoss;

	BackBuffer* m_pBackBuffer;
	ParticleEmitter* m_pParticleEmitter;

	bool m_blockDisable;
	bool m_enemyDisable;
	bool m_bossDisable;

private:

};

#endif // !__LEVEL_H__

