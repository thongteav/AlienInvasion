// This include:
#include "GreenBoss.h"
#include "Game.h"

GreenBoss::GreenBoss()
: Boss()
{

}

GreenBoss::GreenBoss(float x, float y, int width, int height, int health)
: Boss(x, y, width, height, health)
{

}


bool
GreenBoss::Initialise(BackBuffer& backBuffer)
{
	m_pSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\ship-green.png");
	m_pHealthBarSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\hp-bar.png");
	m_pSignalSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\burst-green.png");

	Sprite* m_pSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\laser-green.png");
	m_pLaser = new Laser();
	m_pLaser->Initialise(m_pSprite);

	float x = static_cast<float>(m_x + (m_width - m_pSprite->GetWidth()) / 2);
	float y = static_cast<float>(m_y + m_height);

	m_pLaser->SetPositionX(x);
	m_pLaser->SetPositionY(y);
	m_pLaser->SetWidth((m_pSprite->GetWidth()));

	m_velocityX = 100.0f;
	m_maxAttackTime = 0.5f;
	m_maxMoveTime = 5.0f;
	m_maxSignalTime = 0.5f;

	return (true);
}

void
GreenBoss::Attack(float deltaTime)
{	
	float x = static_cast<float>(m_x + (m_width - m_pLaser->GetWidth()) / 2);
	float height = Entity::Lerp(0.0f, static_cast<float>(Game::HEIGHT - m_pLaser->GetPositionY()), m_timeEllapsed / m_maxAttackTime);

	m_pLaser->SetPositionX(x);
	m_pLaser->SetHeight(static_cast<int>(height));

	if (m_timeEllapsed >= m_maxAttackTime)
	{
		m_pLaser->SetHeight(0);
	}
}