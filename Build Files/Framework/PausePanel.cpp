// This include:
#include "PausePanel.h"

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
	CONTINUE,
	MAIN
};

PausePanel::PausePanel()
: Panel(X, Y, WIDTH, HEIGHT)
{
	Panel::SetDrawBackground(true);
}

void
PausePanel::Initialise(BackBuffer& backBuffer)
{
	Button* continueBtn;
	Button* mainBtn;

	int btnX = X + ((WIDTH - BUTTON_SIZE) / 2);
	int btnY = Y + HEIGHT / 2;

	continueBtn = new Button(btnX, btnY + Y_OFFSET + BUTTON_HEIGHT, BUTTON_SIZE, BUTTON_HEIGHT, "Continue");
	mainBtn = new Button(btnX, btnY + (Y_OFFSET + BUTTON_HEIGHT) * 2, BUTTON_SIZE, BUTTON_HEIGHT, "Main");

	continueBtn->SetHighlighted(true);

	AddButton(continueBtn);
	AddButton(mainBtn);

	Label* label = new Label(btnX, Y + HEIGHT / 4, 200, 20, "Paused");
	AddLabel(label);
}

void
PausePanel::ProcessGameState(Game& game)
{
	Button* pMainBtn = m_pButtons.at(MAIN);
	Button* pContinueBtn = m_pButtons.at(CONTINUE);

	if (pMainBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::MainMenu);
		pMainBtn->Toggle();
	}

	if (pContinueBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::GamePlay);
		pContinueBtn->Toggle();
	}
}