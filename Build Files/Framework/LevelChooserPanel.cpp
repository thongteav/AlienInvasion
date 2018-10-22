// This include:
#include "LevelChooserPanel.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"

// Library includes:
#include <string>

const int WIDTH = Game::WIDTH;
const int HEIGHT = Game::HEIGHT;
const int BUTTON_SIZE = 150;
const int BUTTON_PER_ROW = 4;
const int X_SPACING = (WIDTH - BUTTON_SIZE * BUTTON_PER_ROW) / (BUTTON_PER_ROW + 1);
const int MAX_ROW = 2;
const int Y_INIT = (HEIGHT / 4);
const int Y_SPACING = (HEIGHT - Y_INIT - BUTTON_SIZE * MAX_ROW) / (MAX_ROW + 1);

LevelChooserPanel::LevelChooserPanel()
: Panel(0, 0, WIDTH, HEIGHT)
{

}

void 
LevelChooserPanel::Initialise(BackBuffer& backBuffer)
{
	Panel::SetDrawBackground(false);

	Sprite* sprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\main-menu-black.png");
	GUIComponent::Initialise(sprite);

	int size = BUTTON_PER_ROW * MAX_ROW;

	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < BUTTON_PER_ROW; ++col)
		{
			int x = X_SPACING * (col + 1) + BUTTON_SIZE * col;
			int y = Y_INIT + Y_SPACING * (row + 1) + BUTTON_SIZE * row;

			int num = (row * BUTTON_PER_ROW) + (col + 1);
			std::string label = std::to_string(num);

			Button* b = new Button(x, y, BUTTON_SIZE, BUTTON_SIZE, label.c_str());
			AddButton(b);
		}
	}

	m_pButtons.front()->SetHighlighted(true);

	Label* titleLabel = new Label(WIDTH / 2 - 100, 50, 200, 20, "Choose Level");
	titleLabel->SetTextColour(255, 255, 255);
	AddLabel(titleLabel);
}

void
LevelChooserPanel::ProcessGameState(Game& game)
{
	// Set GameState
	// Set Level
	std::vector<Button*>::iterator iterBtn;
	iterBtn = m_pButtons.begin();

	int level = 1;
	while (iterBtn != m_pButtons.end())
	{
		if ((*iterBtn)->IsPressed())
		{
			game.SetLevel(level);
			game.SetGameState(Game::GameState::GamePlay);
			(*iterBtn)->SetHighlighted(false);
		}

		++level;
		++iterBtn;
	}
}