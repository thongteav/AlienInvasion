// This include:
#include "DebuggingPanel.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Game.h"
#include "Level.h"

const int WIDTH = 400;
const int HEIGHT = 450;
const int X = (Game::WIDTH - WIDTH) / 2; 
const int Y = (Game::HEIGHT - HEIGHT) / 2;
const int BUTTON_SIZE = 190;
const int BUTTON_HEIGHT = 45;
const int Y_OFFSET = 5;

enum Btn
{
	ENEMY,
	BLOCK,
	BOSS,
	EXIT
};

DebuggingPanel::DebuggingPanel()
: Panel(X, Y, WIDTH, HEIGHT)
{
	Panel::SetDrawBackground(true);
}

void
DebuggingPanel::Initialise(BackBuffer& backBuffer)
{
	Button* enemyBtn;
	Button* blockBtn;
	Button* bossBtn;
	Button* exitBtn;

	int btnX = X + ((WIDTH - BUTTON_SIZE) / 2);
	int btnY = Y + HEIGHT / 3;

	enemyBtn = new Button(btnX, btnY + Y_OFFSET + BUTTON_HEIGHT, BUTTON_SIZE, BUTTON_HEIGHT, "Toggle enemies");
	blockBtn = new Button(btnX, btnY + (Y_OFFSET + BUTTON_HEIGHT) * 2, BUTTON_SIZE, BUTTON_HEIGHT, "Toggle blocks");
	bossBtn = new Button(btnX, btnY + (Y_OFFSET + BUTTON_HEIGHT) * 3, BUTTON_SIZE, BUTTON_HEIGHT, "Toggle boss");
	exitBtn = new Button(btnX, btnY + (Y_OFFSET + BUTTON_HEIGHT) * 4, BUTTON_SIZE, BUTTON_HEIGHT, "Continue Game");

	enemyBtn->SetHighlighted(true);
	enemyBtn->SetDebugginig(true);
	blockBtn->SetDebugginig(true);
	bossBtn->SetDebugginig(true);

	AddButton(enemyBtn);
	AddButton(blockBtn);
	AddButton(bossBtn);
	AddButton(exitBtn);

	Label* label = new Label(btnX, Y + HEIGHT / 4, 200, 20, "Debug Menu");
	AddLabel(label);
}

void
DebuggingPanel::ProcessGameState(Game& game)
{
	Button* pEnemyBtn = m_pButtons.at(ENEMY);
	Button* pBlockBtn = m_pButtons.at(BLOCK);
	Button* pBossBtn = m_pButtons.at(BOSS);
	Button* pExitBtn = m_pButtons.at(EXIT);
	
	Level* level = game.GetLevel();

	pEnemyBtn->SetSelected(level->IsEnemyDisable());
	pBlockBtn->SetSelected(level->IsBlockDisable());
	pBossBtn->SetSelected(level->IsBossDisable());

	if (pEnemyBtn->IsPressed())
	{
		level->ToggleEnemyDisable();
		pEnemyBtn->Toggle();
	}

	if (pBlockBtn->IsPressed())
	{
		level->ToggleBlockDisable();
		pBlockBtn->Toggle();
	}

	if (pBossBtn->IsPressed())
	{
		level->ToggleBossDisable();
		pBossBtn->Toggle();
	}

	if (pExitBtn->IsPressed())
	{
		game.SetGameState(Game::GameState::GamePlay);
		pExitBtn->Toggle();
	}
}