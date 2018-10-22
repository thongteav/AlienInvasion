// This include:
#include "Paddle.h"
#include "Dizzy.h"
#include "LogManager.h"
#include <string>

Paddle::Paddle()
: Entity()
, m_totalEllapsedTime(0)
{

}

Paddle::Paddle(float x, float y, int width, int height)
: Entity(x, y, width, height)
, m_totalEllapsedTime(0)
{

}

Paddle::~Paddle()
{
	Entity::~Entity();

	delete m_pDizzy;
	m_pDizzy = 0;
}

void
Paddle::Process(float deltaTime)
{
	if (!m_dizzy)
	{
		Entity::Process(deltaTime);
	}
	else
	{
		m_totalEllapsedTime += deltaTime;

		if (m_totalEllapsedTime > 2.0f)
		{
			m_totalEllapsedTime = 0;
			m_dizzy = false;
		}

		float offsetY = 32;
		m_pDizzy->SetPosition(m_x, m_y - offsetY);
		m_pDizzy->Process(deltaTime);
	}
}

void
Paddle::Draw(BackBuffer& backBuffer)
{
	Entity::Draw(backBuffer);

	if (m_dizzy)
	{
		m_pDizzy->Draw(backBuffer);
	}
}

void
Paddle::SpawnDizzy(BackBuffer& backBuffer)
{
	if (!m_pDizzy)
	{
		int width = 455;
		int frameCounts = 9;
		int size = 64;

		AnimatedSprite* pSprite = backBuffer.CreateAnimatedSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\star-dizzy.png");
		pSprite->SetLooping(true);
		
		m_pDizzy = new Dizzy();
		m_pDizzy->Initialise(pSprite);
		m_pDizzy->SetWidth(size);
		m_pDizzy->SetHeight(size);

		m_pDizzy->AddFrames(width, frameCounts, 0.09f);
		m_pDizzy->StartAnimating();
	}
}

void
Paddle::SetDizzy(bool dizzy)
{
	m_dizzy = dizzy;
}