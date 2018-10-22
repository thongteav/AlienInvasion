// This include:
#include "Level.h"
#include "Game.h"

Level::Level()
: m_pBlocks(0)
, m_pEnemies(0)
, m_pBoss(0)
, m_blockDisable(false)
, m_enemyDisable(false)
, m_bossDisable(false)
{

}

Level::~Level()
{
	DeleteBlocks();
	DeleteEnemies();
	DeleteExplosions();
	DeleteBoss();
}

bool
Level::Initialise(BackBuffer& backBuffer, ParticleEmitter& particleEmitter)
{
	m_pBackBuffer = &backBuffer;
	m_pParticleEmitter = &particleEmitter;

	return (true);
}

void
Level::Process(float deltaTime)
{
	ProcessBlocks(deltaTime);
	ProcessEnemies(deltaTime);
	ProcessExplosions(deltaTime);
	ProcessBoss(deltaTime);
}

void
Level::Draw(BackBuffer& backBuffer)
{
	DrawBoss(backBuffer);
	DrawEnemies(backBuffer);
	DrawBlocks(backBuffer);
}

void
Level::ProcessBlocks(float deltaTime)
{
	// Blocks don't move
}

void
Level::ProcessEnemies(float deltaTime)
{
	if (!m_enemyDisable)
	{
		std::vector<Enemy*>::iterator iterEnemy;

		iterEnemy = m_pEnemies.begin();

		while (iterEnemy != m_pEnemies.end())
		{
			(*iterEnemy)->Process(deltaTime);
			++iterEnemy;
		}
	}
}

void
Level::ProcessBoss(float deltaTime)
{
	if (!m_bossDisable)
	{
		if (m_pBoss)
		{
			m_pBoss->Process(deltaTime);
		}
	}	
}

void
Level::ProcessExplosions(float deltaTime)
{
	std::vector<Explosion*>::iterator iterExplo;
	iterExplo = m_pExplosions.begin();

	while (iterExplo != m_pExplosions.end())
	{
		(*iterExplo)->Process(deltaTime);
		++iterExplo;
	}

	iterExplo = m_pExplosions.begin();
	while (iterExplo != m_pExplosions.end())
	{
		if ((*iterExplo)->IsDead())
		{
			delete (*iterExplo);
			(*iterExplo) = 0;
			iterExplo = m_pExplosions.erase(iterExplo);
		}
		else
		{
			++iterExplo;
		}
	}
}

void
Level::DrawBlocks(BackBuffer& backBuffer)
{
	if (!m_blockDisable)
	{
		std::vector<Block*>::iterator iterBlock;
		iterBlock = m_pBlocks.begin();

		while (iterBlock != m_pBlocks.end())
		{
			if (!(*iterBlock)->IsDead())
			{
				(*iterBlock)->Draw(backBuffer);
			}
			++iterBlock;
		}
	}
}

void
Level::DrawEnemies(BackBuffer& backBuffer)
{
	if (!m_enemyDisable)
	{
		std::vector<Enemy*>::iterator iterEnemy;
		iterEnemy = m_pEnemies.begin();

		while (iterEnemy != m_pEnemies.end())
		{
			if (!(*iterEnemy)->IsDead())
			{
				(*iterEnemy)->Draw(backBuffer);
			}
			++iterEnemy;
		}
	}	
}

void
Level::DrawExplosions(BackBuffer& backBuffer)
{
	std::vector<Explosion*>::iterator iterExplo;
	iterExplo = m_pExplosions.begin();

	while (iterExplo != m_pExplosions.end())
	{
		(*iterExplo)->Draw(backBuffer);
		++iterExplo;
	}
}

void
Level::DrawBoss(BackBuffer& backBuffer)
{
	if (!m_bossDisable)
	{
		if (m_pBoss)
		{
			m_pBoss->Draw(backBuffer);
		}
	}
}

void
Level::DeleteBlocks()
{
	std::vector<Block*>::iterator iterBlock;
	iterBlock = m_pBlocks.begin();

	while (iterBlock != m_pBlocks.end())
	{
		delete (*iterBlock);
		*iterBlock = 0;
		iterBlock = m_pBlocks.erase(iterBlock);
	}
}

void
Level::DeleteEnemies()
{
	std::vector<Enemy*>::iterator iterEnemy;
	iterEnemy = m_pEnemies.begin();

	while (iterEnemy != m_pEnemies.end())
	{
		delete (*iterEnemy);
		*iterEnemy = 0;
		iterEnemy = m_pEnemies.erase(iterEnemy);
	}
}

void
Level::DeleteExplosions()
{
	std::vector<Explosion*>::iterator iterExplo;
	iterExplo = m_pExplosions.begin();

	while (iterExplo != m_pExplosions.end())
	{
		delete (*iterExplo);
		*iterExplo = 0;
		iterExplo = m_pExplosions.erase(iterExplo);
	}
}

void
Level::DeleteBoss()
{
	delete m_pBoss;
	m_pBoss = 0;
}

void
Level::SpawnBlock(float x, float y)
{
	int blockSize = 32;

	Sprite* pSpriteBlock = 0;
	pSpriteBlock = m_pBackBuffer->CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\block.png");

	Block* block = 0;
	block = new Block(x, y, blockSize, blockSize);
	block->Initialise(pSpriteBlock);

	m_pBlocks.push_back(block);
}

void
Level::SpawnEnemy(float x, float y)
{
	int frameCount = 10;
	int frameWidth = 68;
	int frameHeight = 92;
	int enemyWidth = 32;
	int enemyHeight = 48;

	SpriteSheet* pEnemySprite = 0;
	pEnemySprite = m_pBackBuffer->CreateSpriteSheet("..\\..\\Gold Build - 14883251\\Bin\\assets\\enemies.png", frameCount, frameWidth, frameHeight, false);

	Enemy* enemy = 0;
	enemy = new Enemy(x, y, enemyWidth, enemyHeight);
	enemy->Initialise(pEnemySprite);

	m_pEnemies.push_back(enemy);
}

void
Level::SpawnGreenBoss(float x, float y, int health)
{
	int size = 124;

	m_pBoss = new GreenBoss(x, y, size, size, health);
	m_pBoss->Initialise(*m_pBackBuffer);
	m_pBoss->SetString("..\\..\\Gold Build - 14883251\\Bin\\assets\\ship-green-fragment.png");
}

void
Level::SpawnPinkBoss(float x, float y, int health)
{
	int size = 124;

	m_pBoss = new PinkBoss(x, y, size, size, health);
	m_pBoss->Initialise(*m_pBackBuffer);
	m_pBoss->SetString("..\\..\\Gold Build - 14883251\\Bin\\assets\\ship-pink-fragment.png");
}

void
Level::SpawnExplosion(const char* path, float x, float y, int frameCount, float frameSpeed, int explosionSize)
{
	AnimatedSprite* pExploSprite = m_pBackBuffer->CreateAnimatedSprite(path);
	int spriteWidth = pExploSprite->GetWidth() / frameCount;

	for (int i = 0; i < frameCount; ++i)
	{
		pExploSprite->AddFrame(i * spriteWidth);
	}
	pExploSprite->SetFrameWidth(spriteWidth);
	pExploSprite->SetFrameSpeed(frameSpeed);
	pExploSprite->SetX(static_cast<int>(x));
	pExploSprite->SetY(static_cast<int>(y));
	pExploSprite->StartAnimating();

	Explosion* pExplo = new Explosion(x, y, explosionSize, explosionSize);
	pExplo->Initialise(pExploSprite);

	m_pExplosions.push_back(pExplo);
}

void
Level::RestartLevel()
{
	ReviveBlocks();
	ReviveEnemies();
	ReviveBoss();

	m_blockDisable = false;
	m_enemyDisable = false;
	m_bossDisable = false;
}

void
Level::ReviveBlocks()
{
	std::vector<Block*>::iterator iterBlock;
	iterBlock = m_pBlocks.begin();

	while (iterBlock != m_pBlocks.end())
	{
		(*iterBlock)->SetDead(false);
		++iterBlock;
	}
}

void
Level::ReviveEnemies()
{
	std::vector<Enemy*>::iterator iterEnemy;
	iterEnemy = m_pEnemies.begin();

	while (iterEnemy != m_pEnemies.end())
	{
		(*iterEnemy)->Revive();
		++iterEnemy;
	}
}

void
Level::ReviveBoss()
{
	if (m_pBoss)
	{
		m_pBoss->Revive();
	}
}

bool
Level::IsBossAttackHitPaddle(Paddle& paddle)
{
	bool hit = false;

	if (!m_bossDisable)
	{
		if (m_pBoss)
		{
			if (m_pBoss->GetLaser()->IsCollidingWith(paddle))
			{
				paddle.SpawnDizzy(*m_pBackBuffer);
				paddle.SetDizzy(true);
				m_pBoss->GetLaser()->ResetToInitialPosition();
				hit = true;
			}
		}
	}	

	return (hit);
}

bool 
Level::IsBossHitByBall(Ball& ball, float deltaTime)
{
	bool hit = false;

	if (!m_bossDisable)
	{
		if (m_pBoss)
		{
			if (ball.IsCollidingWith(*m_pBoss, deltaTime))
			{
				m_pBoss->LoseHealth();
				hit = true;

				if (m_pBoss->IsDead())
				{
					SpawnExplosion("..\\..\\Gold Build - 14883251\\Bin\\assets\\explosion.png", m_pBoss->GetPositionX(), m_pBoss->GetPositionY(), 6, 0.09f, 124);

					float x = m_pBoss->GetPositionX() + static_cast<float>(m_pBoss->GetWidth() / 2);
					float y = m_pBoss->GetPositionY() + static_cast<float>(m_pBoss->GetHeight() / 2);
					m_pParticleEmitter->SpawnExplosionParticles(15, m_pBoss->GetString(), x, y, *m_pBackBuffer);
				}
			}
		}
	}	

	return (hit);
}

bool 
Level::IsEnemyHitByBall(Ball& ball, float deltaTime)
{
	bool hit = false;

	if (!m_enemyDisable)
	{
		std::vector<Enemy*>::iterator iterEnemy;
		iterEnemy = m_pEnemies.begin();

		while (iterEnemy != m_pEnemies.end())
		{
			Enemy* e = (*iterEnemy);
			if (!(e->IsDead()))
			{
				if (ball.IsCollidingWith(*(*iterEnemy), deltaTime))
				{
					e->NextStatus();
					hit = true;

					if (e->GetStatus() == Enemy::Status::DEAD)
					{
						float x = e->GetPositionX() + static_cast<float>(e->GetWidth() / 2);
						float y = e->GetPositionY() + static_cast<float>(e->GetHeight() / 2);
						SpawnExplosion("..\\..\\Gold Build - 14883251\\Bin\\assets\\explosion2.png", x, y, 5, 0.09f, e->GetHeight());
					}
				}
			}

			++iterEnemy;
		}
	}	

	return (hit);
}

bool 
Level::IsBlockHitByBall(Ball& ball, float deltaTime)
{
	bool hit = false;

	if (!m_blockDisable)
	{
		std::vector<Block*>::iterator iterBlock;

		iterBlock = m_pBlocks.begin();
		while (iterBlock != m_pBlocks.end())
		{
			Block* pBlock = (*iterBlock);
			if (!pBlock->IsDead())
			{
				if (ball.IsCollidingWith(*pBlock, deltaTime))
				{
					pBlock->SetDead(true);
					hit = true;

					Game::GetInstance().SpawnIcePowerUp(pBlock->GetPositionX(), pBlock->GetPositionY());
					m_pParticleEmitter->SpawnExplosionParticles(3, "..\\..\\Gold Build - 14883251\\Bin\\assets\\block-fragment-green.png", pBlock->GetPositionX(), pBlock->GetPositionY(), *m_pBackBuffer);
					m_pParticleEmitter->SpawnExplosionParticles(6, "..\\..\\Gold Build - 14883251\\Bin\\assets\\block-fragment-brown.png", pBlock->GetPositionX(), pBlock->GetPositionY(), *m_pBackBuffer);
				}
			}
			++iterBlock;
		}
	}	

	return (hit);
}

bool
Level::IsLevelCompleted()
{
	bool result = false;
	result = IsBossDead() && AreBlocksDead() && AreEnemiesDead();

	return (result);
}

bool
Level::AreBlocksDead()
{
	bool dead = true;

	if (!m_blockDisable)
	{
		std::vector<Block*>::iterator iterBlock;
		iterBlock = m_pBlocks.begin();

		while (iterBlock != m_pBlocks.end() && dead)
		{
			if (!(*iterBlock)->IsDead())
			{
				dead = false;
			}
			++iterBlock;
		}
	}	

	return (dead);
}

bool
Level::AreEnemiesDead()
{
	bool dead = true;

	if (!m_enemyDisable)
	{
		std::vector<Enemy*>::iterator iterEnemy;
		iterEnemy = m_pEnemies.begin();

		while (iterEnemy != m_pEnemies.end() && dead)
		{
			if (!(*iterEnemy)->IsDead())
			{
				dead = false;
			}
			++iterEnemy;
		}
	}	

	return (dead);
}

bool
Level::IsBossDead()
{
	bool dead = true;

	if (!m_bossDisable)
	{
		if (m_pBoss)
		{
			dead = m_pBoss->IsDead();
		}
	}	

	return (dead);
}

void
Level::ToggleBlockDisable()
{
	m_blockDisable = !m_blockDisable;
}

void
Level::ToggleEnemyDisable()
{
	m_enemyDisable = !m_enemyDisable;
}

void
Level::ToggleBossDisable()
{
	m_bossDisable = !m_bossDisable;
}

bool
Level::IsBlockDisable()
{
	return (m_blockDisable);
}

bool
Level::IsEnemyDisable()
{
	return (m_enemyDisable);
}

bool
Level::IsBossDisable()
{
	return (m_bossDisable);
}


