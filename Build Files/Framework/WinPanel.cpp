// This include:
#include "WinPanel.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"

const int WIDTH = 400;
const int HEIGHT = 350;
const int X = (Game::WIDTH - WIDTH) / 2;
const int Y = (Game::HEIGHT - HEIGHT) / 2;
const int BUTTON_SIZE = 190;
const int BUTTON_HEIGHT = 45;
const int Y_OFFSET = 5;

enum Btn
{
	NEXT,
	RESTART,
	MAIN
};

WinPanel::WinPanel()
: Panel(X, Y, WIDTH, HEIGHT)
{
	Panel::SetDrawBackground(true);
}

void
WinPanel::Initialise(BackBuffer& backBuffer)
{ 
	Button* nextBtn;
	Button* restartBtn;
	Button* mainBtn;

	int btnX = X + ((WIDTH - BUTTON_SIZE) / 2);
	int btnY = Y + HEIGHT / 2;

	nextBtn = new Button(btnX, btnY, BUTTON_SIZE, BUTTON_HEIGHT, "Next Level");
	restartBtn = new Button(btnX, btnY + Y_OFFSET + BUTTON_HEIGHT, BUTTON_SIZE, BUTTON_HEIGHT, "Replay");
	mainBtn = new Button(btnX, btnY + Y_OFFSET * 2 + BUTTON_HEIGHT * 2, BUTTON_SIZE, BUTTON_HEIGHT, "Main");
	
	nextBtn->SetHighlighted(true);

	AddButton(nextBtn);
	AddButton(restartBtn);
	AddButton(mainBtn);

	Label* label = new Label(btnX, Y + HEIGHT / 4, 200, 20, "Victory!");
	AddLabel(label);
}

void
WinPanel::ProcessGameState(Game& game)
{
	Button* pMainBtn = m_pButtons.at(MAIN);
	Button* pRestartBtn = m_pButtons.at(RESTART);
	Button* pNextBtn = m_pButtons.at(NEXT);

	if (pMainBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::MainMenu);
		pMainBtn->Toggle();
	}

	if (pRestartBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::GamePlay);
		pRestartBtn->Toggle();
	}

	if (pNextBtn->IsPressed())
	{
		game.NextLevel();
		game.SetGameState(Game::GameState::GamePlay);
		pNextBtn->Toggle();
	}
}