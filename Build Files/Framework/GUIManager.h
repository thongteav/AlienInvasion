#pragma once

#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

// Local includes:
#include "WinPanel.h"
#include "LosePanel.h"
#include "MainMenuPanel.h"
#include "SplashScreenPanel.h"
#include "PausePanel.h"
#include "LevelChooserPanel.h"
#include "BackBuffer.h"
#include "DebuggingPanel.h"
#include "InstructionPanel.h"

class GUIManager
{
	// Member Methods:
public:
	GUIManager();
	~GUIManager();

	bool Initialise(BackBuffer& backBuffer);

	void Process(Game::GameState state, float deltaTime);
	void ProcessGameState(Game::GameState state, Game& game);
	void Draw(Game::GameState state, BackBuffer& backBuffer);

	void NextButton(Game::GameState state);
	void PreviousButton(Game::GameState state);
	void PressButton(Game::GameState state);
	void PressButton(Game::GameState state, int x, int y);
	void HoverOnButton(Game::GameState state, int x, int y);

	void ResetButtons(Game::GameState);

protected:

private:

	// Member Fields:
public:

protected:

private:
	WinPanel * m_pWinPanel;
	LosePanel* m_pLosePanel;
	MainMenuPanel* m_pMainMenuPanel;
	SplashScreenPanel* m_pSplashScreenPanel;
	PausePanel* m_pPausePanel;
	LevelChooserPanel* m_pLevelChooserPanel;
	DebuggingPanel* m_pDebuggingPanel;
	InstructionPanel* m_pInstructionPanel;
};

#endif // !__GUI_MANAGER_H__
