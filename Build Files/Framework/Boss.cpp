// This include:
#include "Boss.h"
#include "Game.h"
#include "LogManager.h"

Boss::Boss()
: Entity()
, m_health(0)
, m_timeEllapsed(0)
{

}

Boss::Boss(float x, float y, int width, int height, int health)
: Entity(x, y, width, height)
, m_health(health)
, m_timeEllapsed(0)
, m_maxHealth(health)
, m_healthBarLength(200)
{

}

Boss::~Boss()
{
	Entity::~Entity();

	delete m_pHealthBarSprite;
	m_pHealthBarSprite = 0;

	delete m_pSignalSprite;
	m_pSignalSprite = 0;

	delete m_pLaser;
	m_pLaser = 0;
}

void
Boss::Process(float deltaTime)
{
	if (!m_dead)
	{
		switch (m_currentState)
		{
		case Boss::State::MOVE:
			m_timeEllapsed += deltaTime;

			Move(deltaTime);

			if (m_timeEllapsed > m_maxMoveTime)
			{
				m_currentState = Boss::State::SIGNAL;
				m_timeEllapsed = 0;
			}

			break;

		case Boss::State::SIGNAL:
			m_timeEllapsed += deltaTime;

			Signal(deltaTime);

			if (m_timeEllapsed > m_maxSignalTime)
			{
				m_currentState = Boss::State::ATTACK;
				m_timeEllapsed = 0;

				SetInitialAttackPosition();
			}

			break;
		case Boss::State::ATTACK:
			m_pLaser->SetDead(false);
			m_timeEllapsed += deltaTime;

			Attack(deltaTime);

			if (m_timeEllapsed > m_maxAttackTime)
			{
				m_currentState = Boss::State::MOVE;
				m_timeEllapsed = 0;
			}

			break;
		}

		ProcessHealth();
	}
}

void
Boss::ProcessHealth()
{
	if (m_health <= 0)
	{
		m_dead = true;
	}
}

void
Boss::Draw(BackBuffer& backBuffer)
{
	if (!m_dead)
	{
		switch (m_currentState)
		{
		case Boss::MOVE:
			break;
		case Boss::SIGNAL:
			DrawSignal(backBuffer);
			break;
		case Boss::ATTACK:
			DrawAttack(backBuffer);
			break;
		}

		Entity::DrawInDimension(backBuffer);

		DrawHealthBar(backBuffer);
	}	
}

void
Boss::DrawSignal(BackBuffer& backBuffer)
{
	m_pSignalSprite->SetX(static_cast<int>(m_x));
	m_pSignalSprite->SetY(static_cast<int>(m_y));
	m_pSignalSprite->Draw(backBuffer);
}

void
Boss::DrawAttack(BackBuffer& backBuffer)
{
	m_pLaser->Draw(backBuffer);
}

void
Boss::DrawHealthBar(BackBuffer& backBuffer)
{
	int width = m_healthBarLength * m_health / m_maxHealth;
	int height = m_pHealthBarSprite->GetHeight();

	int x = (Game::WIDTH - m_healthBarLength) / 2;
	int yOffset = 10;
	m_pHealthBarSprite->SetX(x);
	m_pHealthBarSprite->SetY(yOffset);
	m_pHealthBarSprite->Draw(backBuffer, width, height);

	int textWidth = 80;
	int rectOffset = 3;

	backBuffer.SetTextColour(255, 255, 255);
	backBuffer.DrawText(x - textWidth, yOffset / 2, "Health: ");

	backBuffer.SetDrawColour(255, 255, 255, 255);
	backBuffer.DrawRectangle(x, yOffset, m_healthBarLength, height, rectOffset);
}

void
Boss::LoseHealth()
{
	--m_health;

	ProcessHealth();
}

void
Boss::Move(float deltaTime)
{
	Paddle* pPaddle = Game::GetInstance().GetPaddle();
	float paddleX = pPaddle->GetPositionX();
	float deadZone = (m_velocityX * deltaTime) * 2;

	if (m_x > paddleX + deadZone)
	{
		m_x = m_x - m_velocityX * deltaTime;
	}
	else if (m_x < paddleX - deadZone)
	{
		m_x = m_x + m_velocityX * deltaTime;
	}
}

void
Boss::Attack(float deltaTime)
{
	// No body implementation
}

void
Boss::Signal(float deltaTime)
{
	// No body implementation
}

Laser*
Boss::GetLaser()
{
	return (m_pLaser);
}

void
Boss::Revive()
{
	m_health = m_maxHealth;
	m_dead = false;
}

bool
Boss::IsDead()
{
	return (m_health <= 0);
}

const char*
Boss::GetString()
{
	return (m_fragmentString);
}

void
Boss::SetString(const char* string)
{
	m_fragmentString = string;
}

void
Boss::SetInitialAttackPosition()
{
	int laserWidth = m_pLaser->GetWidth();

	float x = static_cast<float>(m_x + (m_width - laserWidth) / 2);
	float y = static_cast<float>(m_y + m_height);

	m_pLaser->SetInitialPosition(x, y);
}