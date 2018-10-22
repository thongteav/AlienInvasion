// This include:
#include "MainMenuPanel.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"

const int WIDTH = Game::WIDTH;
const int HEIGHT = Game::HEIGHT;
const int BUTTON_SIZE = 190;
const int BUTTON_HEIGHT = 45;
const int Y_OFFSET = 5;

enum Btn
{
	PLAY,
	INSTRUCTION,
	CREDIT
};

MainMenuPanel::MainMenuPanel()
: Panel(0, 0, WIDTH, HEIGHT)
{

}

void
MainMenuPanel::Initialise(BackBuffer& backBuffer)
{
	Panel::SetDrawBackground(true);
	Panel::SetBackgroundColour(255, 255, 255, 255);

	Sprite* sprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\main-menu-space.png");
	GUIComponent::Initialise(sprite);

	Button* playBtn;
	Button* instructionBtn;
	Button* creditBtn;

	int btnX = (WIDTH - BUTTON_SIZE) / 2;
	int btnY = HEIGHT * 5 / 8;

	playBtn = new Button(btnX, btnY, BUTTON_SIZE, BUTTON_HEIGHT, "Play");
	instructionBtn = new Button(btnX, btnY + Y_OFFSET + BUTTON_HEIGHT, BUTTON_SIZE, BUTTON_HEIGHT, "Instruction");
	creditBtn = new Button(btnX, btnY + (Y_OFFSET + BUTTON_HEIGHT) * 2, BUTTON_SIZE, BUTTON_HEIGHT, "Credits");

	playBtn->SetHighlighted(true);

	AddButton(playBtn);
	AddButton(instructionBtn);
	AddButton(creditBtn);

	Label* titleLabel = new Label(btnX, HEIGHT / 4, 200, 20, "Alien Invasion");
	titleLabel->SetTextColour(255, 255, 255);
	AddLabel(titleLabel);
}

void
MainMenuPanel::ProcessGameState(Game& game)
{
	Button* pPlayBtn = m_pButtons.at(PLAY);
	if (pPlayBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::ChooseLevel);
		pPlayBtn->Toggle();
	}

	Button* pInstructionBtn = m_pButtons.at(INSTRUCTION);
	if (pInstructionBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::Instruction);
		pInstructionBtn->Toggle();
	}
}