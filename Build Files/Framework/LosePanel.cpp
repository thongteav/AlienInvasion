// This include:
#include "LosePanel.h"

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
	RESTART,
	MAIN
};

LosePanel::LosePanel()
: Panel(X, Y, WIDTH, HEIGHT)
{
	Panel::SetDrawBackground(true);
}

void
LosePanel::Initialise(BackBuffer& backBuffer)
{
	Button* restartBtn;
	Button* mainBtn;

	int btnX = X + ((WIDTH - BUTTON_SIZE) / 2);
	int btnY = Y + HEIGHT / 2;

	restartBtn = new Button(btnX, btnY + Y_OFFSET + BUTTON_HEIGHT, BUTTON_SIZE, BUTTON_HEIGHT, "Replay");
	mainBtn = new Button(btnX, btnY + (Y_OFFSET + BUTTON_HEIGHT) * 2, BUTTON_SIZE, BUTTON_HEIGHT, "Main");

	restartBtn->SetHighlighted(true);

	AddButton(restartBtn);
	AddButton(mainBtn);

	Label* label = new Label(btnX, Y + HEIGHT / 4, 200, 20, "Level failed!");
	AddLabel(label);
}

void
LosePanel::ProcessGameState(Game& game)
{
	Button* pMainBtn = m_pButtons.at(MAIN);
	Button* pRestartBtn = m_pButtons.at(RESTART);

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
}