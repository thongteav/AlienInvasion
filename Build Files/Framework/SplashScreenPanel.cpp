// This include:
#include "SplashScreenPanel.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"

const float MAX_TIME = 3.0f;
const float MAX_TRANSITION_TIME = 1.0f;

SplashScreenPanel::SplashScreenPanel()
: Panel(0, 0, Game::WIDTH, Game::HEIGHT)
, m_totalEllapsedTime(0)
, m_animating(true)
{
	m_a = 255;
}

void
SplashScreenPanel::Initialise(BackBuffer& backBuffer)
{
	Sprite* sprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\aut-logo-splash.png");
	GUIComponent::Initialise(sprite);
}

void
SplashScreenPanel::Process(float deltaTime)
{
	if (m_totalEllapsedTime < MAX_TIME)
	{
		m_totalEllapsedTime += deltaTime;
	}

	if (m_animating && m_totalEllapsedTime < MAX_TRANSITION_TIME)
	{
		float alpha = Lerp(0.0f, 255.0f, (m_totalEllapsedTime / MAX_TRANSITION_TIME));
		m_a = static_cast<unsigned char>(alpha);
	}
}

void
SplashScreenPanel::ProcessGameState(Game& game)
{
	if (m_totalEllapsedTime > 3.0f)
	{
		game.SetGameState(Game::GameState::MainMenu);
	}
}

float
SplashScreenPanel::Lerp(float initial, float final, float difference)
{
	float result;
	result = (1.0f - difference) * initial + difference * final;

	return (result);
}

void
SplashScreenPanel::Draw(BackBuffer& backBuffer)
{
	if (m_pSprite)
	{
		backBuffer.DrawSprite(*m_pSprite, Game::WIDTH, Game::HEIGHT, m_a);
	}
}

