// This include:
#include "InstructionPanel.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"

const int BUTTON_SIZE = 190;
const int BUTTON_HEIGHT = 45;
const int Y_OFFSET = 5;

InstructionPanel::InstructionPanel()
: Panel(0, 0, Game::WIDTH, Game::HEIGHT)
{
	Panel::SetDrawBackground(true);
}

void
InstructionPanel::Initialise(BackBuffer& backBuffer)
{
	int btnX = (Game::WIDTH - BUTTON_SIZE) / 2;
	int btnY = Game::HEIGHT - Y_OFFSET - BUTTON_HEIGHT;

	Button* mainBtn;
	mainBtn = new Button(btnX, btnY, BUTTON_SIZE, BUTTON_HEIGHT, "Main");
	mainBtn->SetHighlighted(true);

	AddButton(mainBtn);

	Label* label = new Label(btnX, 25, BUTTON_SIZE, 20, "Instruction");

	std::string msg;
	msg.append("Clear all the blocks and enemies on each level.");
	msg.append("You control a paddle that can move horizontally ");
	msg.append("and to keep the ball from falling to the bottom. ");
	msg.append("The block may drop a power-up occasionally when destroyed. ");
	msg.append("If you lose all three lives, you fail the level. ");

	Label* instruction = new Label(50, 80, 700, 50, msg.c_str());

	Label* controlLbl = new Label(btnX, 150, BUTTON_SIZE, 20, "Control");
	Label* control = new Label(45, 170, 780, 300, "");
	Sprite* pSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\control.png");
	control->Initialise(pSprite);

	AddLabel(label);
	AddLabel(instruction);
	AddLabel(controlLbl);
	AddLabel(control);
}

void
InstructionPanel::DrawLabels(BackBuffer& backBuffer)
{
	std::vector<Label*>::iterator iterLabel;
	iterLabel = m_pLabels.begin();

	while (iterLabel != m_pLabels.end())
	{
		(*iterLabel)->DrawWrapped(backBuffer);
		++iterLabel;
	}
}

void
InstructionPanel::ProcessGameState(Game& game)
{
	if (m_pButtons.front()->IsPressed())
	{
		game.SetGameState(Game::GameState::MainMenu);
	}
}
