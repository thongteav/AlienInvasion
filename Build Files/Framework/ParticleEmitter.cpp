// This include:
#include "ParticleEmitter.h"

// Local includes:
#include "Game.h"
#include "Sprite.h"

ParticleEmitter::ParticleEmitter()
: m_pStars(0)
, m_pExplosions(0)
{

}

ParticleEmitter::~ParticleEmitter()
{
	DeleteStars();
	DeleteExplosions();
}

void
ParticleEmitter::DeleteStars()
{
	std::vector<StarParticle*>::iterator iterStar;
	iterStar = m_pStars.begin();

	while (iterStar != m_pStars.end())
	{
		delete (*iterStar);
		(*iterStar) = 0;
		iterStar = m_pStars.erase(iterStar);
	}
}

void
ParticleEmitter::DeleteExplosions()
{
	std::vector<ExplosionParticle*>::iterator iterExplo;
	iterExplo = m_pExplosions.begin();

	while (iterExplo != m_pExplosions.end())
	{
		delete (*iterExplo);
		(*iterExplo) = 0;
		iterExplo = m_pExplosions.erase(iterExplo);
	}
}

bool
ParticleEmitter::Initialise(BackBuffer& backBuffer)
{
	SpawnBigStars(30, backBuffer);
	SpawnSmallStars(20, backBuffer);

	return (true);
}

void
ParticleEmitter::SpawnBigStars(int count, BackBuffer& backBuffer)
{
	SpawnStars(count, "..\\..\\Gold Build - 14883251\\Bin\\assets\\biggerstar.png", 180.0f, backBuffer);
}

void
ParticleEmitter::SpawnSmallStars(int count, BackBuffer& backBuffer)
{
	SpawnStars(count, "..\\..\\Gold Build - 14883251\\Bin\\assets\\smallstar.png", 100.0f, backBuffer);
}

void
ParticleEmitter::SpawnStars(int count, const char* path, float speed, BackBuffer& backBuffer)
{
	for (int i = 0; i < count; ++i)
	{
		float x = static_cast<float>(rand() % Game::WIDTH);
		float y = static_cast<float>(rand() % Game::HEIGHT);

		Sprite* p_StarSprite = backBuffer.CreateSprite(path);

		StarParticle* star;
		star = new StarParticle();
		star->SetPosition(x, y);
		star->SetVerticalVelocity(speed);

		star->Initialise(p_StarSprite);
		m_pStars.push_back(star);
	}
}

void
ParticleEmitter::SpawnExplosionParticles(int count, const char* path, float x, float y, BackBuffer& backBuffer)
{
	for (int i = 0; i < count; ++i)
	{
		float spriteAngle = static_cast<float>(rand() % 360);
		Sprite* pExploSprite = backBuffer.CreateSprite(path);
		pExploSprite->SetAngle(spriteAngle);

		float exploAngle = static_cast<float>(rand() % 360);
		float maxAge = static_cast<float>(rand() % 8 + 2) / 10.0f;
		float velocityX = static_cast<float>(rand() % 100 + 100);
		float velocityY = static_cast<float>(rand() % 100 + 100);
		ExplosionParticle* pExploParticle = new ExplosionParticle();
		pExploParticle->SetAngle(exploAngle);
		pExploParticle->SetPosition(x, y);
		pExploParticle->Initialise(pExploSprite);
		pExploParticle->SetMaxAge(maxAge);
		pExploParticle->SetHorizontalVelocity(velocityX);
		pExploParticle->SetVerticalVelocity(velocityY);

		m_pExplosions.push_back(pExploParticle);
	}
}

void
ParticleEmitter::Process(float deltaTime)
{
	ProcessStars(deltaTime);
	ProcessExplosions(deltaTime);
}

void
ParticleEmitter::Draw(BackBuffer& backBuffer)
{
	DrawStars(backBuffer);
	DrawExplosions(backBuffer);
}

void
ParticleEmitter::ProcessStars(float deltaTime)
{
	std::vector<StarParticle*>::iterator iterStar;
	iterStar = m_pStars.begin();

	while (iterStar != m_pStars.end())
	{
		(*iterStar)->Process(deltaTime);
		++iterStar;
	}
}

void
ParticleEmitter::ProcessExplosions(float deltaTime)
{
	std::vector<ExplosionParticle*>::iterator iterExplo;
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
ParticleEmitter::DrawStars(BackBuffer& backBuffer)
{
	std::vector<StarParticle*>::iterator iterStar;
	iterStar = m_pStars.begin();

	while (iterStar != m_pStars.end())
	{
		(*iterStar)->Draw(backBuffer);
		++iterStar;
	}
}

void
ParticleEmitter::DrawExplosions(BackBuffer& backBuffer)
{
	std::vector<ExplosionParticle*>::iterator iterExplo;
	iterExplo = m_pExplosions.begin();

	while (iterExplo != m_pExplosions.end())
	{
		(*iterExplo)->Draw(backBuffer);
		++iterExplo;
	}
}