// This include:
#include "PinkBoss.h"
#include "Game.h"

PinkBoss::PinkBoss()
: Boss()
{
	
}

PinkBoss::PinkBoss(float x, float y, int width, int height, int health)
: Boss(x, y, width, height, health)
{

}

bool
PinkBoss::Initialise(BackBuffer& backBuffer)
{
	m_pSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\ship-pink.png");
	m_pHealthBarSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\hp-bar.png");
	m_pSignalSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\burst-pink.png");
	
	Sprite* pRingSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\laser-pink.png");
	m_pLaser = new Laser(0, 0, pRingSprite->GetWidth(), pRingSprite->GetHeight());
	m_pLaser->Initialise(pRingSprite);

	m_velocityX = 50.0f;
	m_maxAttackTime = 1.0f;
	m_maxMoveTime = 5.0f;
	m_maxSignalTime = 1.5f;

	return (true);
}

void
PinkBoss::GetInitAttackPosition()
{
	int laserWidth = m_pLaser->GetWidth();

	m_attackInitX = static_cast<float>(m_x + (m_width - laserWidth) / 2);
	m_attackInitY = static_cast<float>(m_y + m_height);
}

void
PinkBoss::GetFinalAttackPosition()
{
	Paddle* pPaddle = Game::GetInstance().GetPaddle();

	m_attackFinalX = pPaddle->GetPositionX();
	m_attackFinalY = pPaddle->GetPositionY();
}

void
PinkBoss::Attack(float deltaTime)
{
	// Shoot a round laser
	float attackX = Lerp(m_attackInitX, m_attackFinalX, m_timeEllapsed / m_maxAttackTime);
	float attackY = Lerp(m_attackInitY, m_attackFinalY, m_timeEllapsed / m_maxAttackTime);

	m_pLaser->SetPosition(attackX, attackY);

	if (m_timeEllapsed >= m_maxAttackTime)
	{
		ResetLaserPosition();
	}
}

void
PinkBoss::Signal(float deltaTime)
{
	GetInitAttackPosition();
	GetFinalAttackPosition();
}

void
PinkBoss::DrawAttack(BackBuffer& backBuffer)
{
	Boss::DrawAttack(backBuffer);
}

void
PinkBoss::ResetLaserPosition()
{
	m_pLaser->SetPosition(m_attackInitX, m_attackInitY);
}