// This include:
#include "LevelManager.h"

// Local includes:
#include "Level.h"
#include "Game.h"
#include "LogManager.h"

// Library includes:
#include <string>

const int BlOCKSIZE = 32;
const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 48;
const int BOSS_INIT_Y = 30;
const int BOSS_SIZE = 124;
const int MAX_LEVEL = 8;

LevelManager::LevelManager()
: m_currentLevel(1)
, m_pLevel(0)
, m_pBackBuffer(0)
, m_pParticleEmitter(0)
{

}

LevelManager::~LevelManager()
{
	DeleteLevel();

	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
}

void
LevelManager::DeleteLevel()
{
	delete m_pLevel;
	m_pLevel = 0;
}

bool
LevelManager::Initialise(BackBuffer& backBuffer)
{
	m_pBackBuffer = &backBuffer;
	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->Initialise(backBuffer);

	return (true);
}

void
LevelManager::Process(float deltaTime)
{
	m_pLevel->Process(deltaTime);
	m_pParticleEmitter->Process(deltaTime);
}

void
LevelManager::Draw(BackBuffer& backBuffer)
{
	m_pLevel->Draw(backBuffer);
	m_pParticleEmitter->Draw(backBuffer); //Draw Fragments on top of explosion
	m_pLevel->DrawExplosions(backBuffer);
}

void
LevelManager::NextLevel()
{
	if (m_currentLevel < MAX_LEVEL && m_currentLevel > 0)
	{
		++m_currentLevel;
	}
}

void
LevelManager::SetLevel(int level)
{
	m_currentLevel = level;

	// boundary checking
	if (level > MAX_LEVEL)
	{
		m_currentLevel = MAX_LEVEL;
	}
	else if (level <= 0)
	{
		m_currentLevel = 1;
	}
}

void
LevelManager::StartLevel()
{
	if (m_pLevel)
	{
		DeleteLevel();
	}

	Level* level = new Level();
	level->Initialise(*m_pBackBuffer, *m_pParticleEmitter);

	m_pLevel = level;

	switch (m_currentLevel)
	{
		case 1:
			StartLevel1();
			break;
		case 2:
			StartLevel2();
			break;
		case 3:
			StartLevel3();
			break;
		case 4:
			StartLevel4();
			break;
		case 5:
			StartLevel5();
			break;
		case 6:
			StartLevel6();
			break;
		case 7:
			StartLevel7();
			break;
		case 8:
			StartLevel8();
			break;
		default:
			break;
	}
}

void
LevelManager::RestartLevel()
{
	m_pLevel->RestartLevel();
}

bool
LevelManager::IsLevelCompleted()
{
	return (m_pLevel->IsLevelCompleted());
}

bool
LevelManager::IsBossAttackHitPaddle(Paddle& paddle)
{
	return (m_pLevel->IsBossAttackHitPaddle(paddle));
}

bool
LevelManager::IsBossHitByBall(Ball& ball, float deltaTime)
{
	return (m_pLevel->IsBossHitByBall(ball, deltaTime));
}

bool 
LevelManager::IsEnemyHitByBall(Ball& ball, float deltaTime)
{
	return (m_pLevel->IsEnemyHitByBall(ball, deltaTime));
}

bool 
LevelManager::IsBlockHitByBall(Ball& ball, float deltaTime)
{
	return (m_pLevel->IsBlockHitByBall(ball, deltaTime));
}

ParticleEmitter*
LevelManager::GetParticleEmitter()
{
	return (m_pParticleEmitter);
}

Level*
LevelManager::GetLevel()
{
	return (m_pLevel);
}

void 
LevelManager::StartLevel1()
{
	//Spawn Five Block

	int count = 5;
	float y = 50.0f;
	int initX = (Game::WIDTH - (BlOCKSIZE * count)) / 2;

	for (int i = 0; i < count; ++i)
	{
		m_pLevel->SpawnBlock(static_cast<float>(initX + i * BlOCKSIZE), y);
	}
}

void
LevelManager::StartLevel2()
{
	float y = 50;
	int x = (Game::WIDTH - ENEMY_WIDTH) / 2;
	float offsetX = 100;

	m_pLevel->SpawnEnemy(static_cast<float>(x), y);
	m_pLevel->SpawnEnemy(static_cast<float>(Game::WIDTH - offsetX), y);
	m_pLevel->SpawnEnemy(offsetX, y);
}

void
LevelManager::StartLevel3()
{
	int count = 7;
	int initX = (Game::WIDTH - (BlOCKSIZE * count)) / 2;
	int initY = 50;

	for (int i = 0; i < count; ++i)
	{
		int y = 0;

		if (i % 2 == 0)
		{
			y = initY;
		}
		else
		{
			y = initY + BlOCKSIZE;
		}

		m_pLevel->SpawnBlock(static_cast<float>(initX + i * BlOCKSIZE), static_cast<float>(y));
	}
}

void
LevelManager::StartLevel4()
{
	int health = 10;
	float bossX = static_cast<float>((Game::WIDTH - BOSS_SIZE) / 2);

	m_pLevel->SpawnGreenBoss(bossX, static_cast<float>(BOSS_INIT_Y), health);

	int enemyOffsetX = 60;
	float enemyY = ENEMY_HEIGHT * 4;
	m_pLevel->SpawnEnemy(static_cast<float>(enemyOffsetX), enemyY);
	m_pLevel->SpawnEnemy(static_cast<float>(Game::WIDTH - enemyOffsetX - ENEMY_WIDTH), enemyY);
}

void
LevelManager::StartLevel5()
{
	int countPerRow = 6;
	int row = 3;
	int initX = (Game::WIDTH - BlOCKSIZE * countPerRow) / 2;
	int initY = 50;


	for (int j = 0; j < row; ++j)
	{
		for (int i = 0; i < countPerRow; ++i)
		{
			m_pLevel->SpawnBlock(static_cast<float>(initX + i * BlOCKSIZE), static_cast<float>(initY + j * (BlOCKSIZE * 2)));
		}
	}

	m_pLevel->SpawnBlock(static_cast<float>(initX), static_cast<float>(initY + BlOCKSIZE));
	m_pLevel->SpawnBlock(static_cast<float>(initX + ((countPerRow - 1) * BlOCKSIZE)), static_cast<float>(initY + BlOCKSIZE * row));
}

void
LevelManager::StartLevel6()
{
	int row = 5;
	int col = row + (row - 1);
	int initX = (Game::WIDTH - BlOCKSIZE * col) / 2;
	int initY = 32;

	for (int j = 0; j < row; ++j)
	{
		for (int i = 0; i < col; ++i)
		{
			if (i >= j && i < col - j)
			{
				m_pLevel->SpawnBlock(static_cast<float>(initX + (BlOCKSIZE * i)), static_cast<float>(initY + (BlOCKSIZE * j)));
			}
		}
	}
}

void
LevelManager::StartLevel7()
{
	int count = Game::WIDTH / BlOCKSIZE;

	for (int i = 0; i < count; ++i)
	{
		m_pLevel->SpawnBlock(static_cast<float>(i * BlOCKSIZE), static_cast<float>(Game::HEIGHT / 2));
	}

	int enemiesCount = 5;
	float xOffset = static_cast<float>(Game::WIDTH - ENEMY_WIDTH * enemiesCount) / static_cast<float>(enemiesCount + 1);
	float initY = 50;

	for (int i = 0; i < enemiesCount; ++i)
	{
		float x = xOffset * static_cast<float>(i + 1) + static_cast<float>(ENEMY_WIDTH * i);
		if (i % 2 == 0)
		{
			m_pLevel->SpawnEnemy(x, initY);
		}
		else
		{
			m_pLevel->SpawnEnemy(x, initY + static_cast<float>(ENEMY_WIDTH));
		}
	}
}

void
LevelManager::StartLevel8()
{
	int health = 15;
	float bossX = static_cast<float>((Game::WIDTH - BOSS_SIZE) / 2);

	m_pLevel->SpawnPinkBoss(bossX, static_cast<float>(BOSS_INIT_Y), health);

	float initY = 180;
	int row = 3;
	int xOffset = 100;

	for (int i = 0; i < row; ++i)
	{
		m_pLevel->SpawnBlock(static_cast<float>(xOffset + ENEMY_WIDTH * i), initY + static_cast<float>(BlOCKSIZE * i));
		m_pLevel->SpawnBlock(static_cast<float>(Game::WIDTH - ENEMY_WIDTH * i - xOffset), initY + static_cast<float>(BlOCKSIZE * i));
	}


	float xGap = 50;
	int count = 4;
	float initX = static_cast<float>((Game::WIDTH - (count * ENEMY_WIDTH) - (xGap * (count - 1)))/ 2);

	for (int i = 0; i < count; ++i)
	{
		m_pLevel->SpawnEnemy(initX + static_cast<float>(i * (ENEMY_WIDTH + xGap)), initY);
	}
}
