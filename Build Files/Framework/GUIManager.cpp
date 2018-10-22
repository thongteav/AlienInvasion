// This include:
#include "GUIManager.h"

GUIManager::GUIManager()
{

}

GUIManager::~GUIManager()
{
	delete m_pWinPanel;
	m_pWinPanel = 0;

	delete m_pLosePanel;
	m_pLosePanel = 0;

	delete m_pMainMenuPanel;
	m_pMainMenuPanel = 0;

	delete m_pSplashScreenPanel;
	m_pSplashScreenPanel = 0;

	delete m_pPausePanel;
	m_pPausePanel = 0;

	delete m_pLevelChooserPanel;
	m_pLevelChooserPanel = 0;

	delete m_pDebuggingPanel;
	m_pDebuggingPanel = 0;

	delete m_pInstructionPanel;
	m_pInstructionPanel = 0;
}

bool
GUIManager::Initialise(BackBuffer& backBuffer)
{
	m_pWinPanel = new WinPanel();
	m_pWinPanel->Initialise(backBuffer);

	m_pLosePanel = new LosePanel();
	m_pLosePanel->Initialise(backBuffer);

	m_pMainMenuPanel = new MainMenuPanel();
	m_pMainMenuPanel->Initialise(backBuffer);

	m_pSplashScreenPanel = new SplashScreenPanel();
	m_pSplashScreenPanel->Initialise(backBuffer);

	m_pPausePanel = new PausePanel();
	m_pPausePanel->Initialise(backBuffer);

	m_pLevelChooserPanel = new LevelChooserPanel();
	m_pLevelChooserPanel->Initialise(backBuffer);

	m_pDebuggingPanel = new DebuggingPanel();
	m_pDebuggingPanel->Initialise(backBuffer);

	m_pInstructionPanel = new InstructionPanel();
	m_pInstructionPanel->Initialise(backBuffer);

	return (true);
}

void
GUIManager::Process(Game::GameState state, float deltaTime)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		m_pSplashScreenPanel->Process(deltaTime);
		break;
	default:
		break;
	}
}

void
GUIManager::ProcessGameState(Game::GameState state, Game& game)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		m_pSplashScreenPanel->ProcessGameState(game);
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->ProcessGameState(game);
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->ProcessGameState(game);
		break;
	case Game::GameState::Win:
		m_pWinPanel->ProcessGameState(game);
		break;
	case Game::GameState::Lose:
		m_pLosePanel->ProcessGameState(game);
		break;
	case Game::GameState::Pause:
		m_pPausePanel->ProcessGameState(game);
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->ProcessGameState(game);
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->ProcessGameState(game);
	default:
		break;
	}
}

void
GUIManager::Draw(Game::GameState state, BackBuffer& backBuffer)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		m_pSplashScreenPanel->Draw(backBuffer);
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->Draw(backBuffer);
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->Draw(backBuffer);
		break;
	case Game::GameState::GamePlay:
		break;
	case Game::GameState::Win:
		m_pWinPanel->Draw(backBuffer);
		break;
	case Game::GameState::Lose:
		m_pLosePanel->Draw(backBuffer);
		break;
	case Game::GameState::Pause:
		m_pPausePanel->Draw(backBuffer);
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->Draw(backBuffer);
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->Draw(backBuffer);
		break;
	default:
		break;
	}
}

void
GUIManager::NextButton(Game::GameState state)
{
	switch (state)
	{
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->NextButton();
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->NextButton();
		break;
	case Game::GameState::Win:
		m_pWinPanel->NextButton();
		break;
	case Game::GameState::Lose:
		m_pLosePanel->NextButton();
		break;
	case Game::GameState::Pause:
		m_pPausePanel->NextButton();
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->NextButton();
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->NextButton();
		break;
	default:
		break;
	}
}

void
GUIManager::PreviousButton(Game::GameState state)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->PreviousButton();
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->PreviousButton();
		break;
	case Game::GameState::GamePlay:
		break;
	case Game::GameState::Win:
		m_pWinPanel->PreviousButton();
		break;
	case Game::GameState::Lose:
		m_pLosePanel->PreviousButton();
		break;
	case Game::GameState::Pause:
		m_pPausePanel->PreviousButton();
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->PreviousButton();
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->PreviousButton();
		break;
	default:
		break;
	}
}

void
GUIManager::PressButton(Game::GameState state)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->PressButton();
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->PressButton();
		break;
	case Game::GameState::GamePlay:
		break;
	case Game::GameState::Win:
		m_pWinPanel->PressButton();
		break;
	case Game::GameState::Lose:
		m_pLosePanel->PressButton();
		break;
	case Game::GameState::Pause:
		m_pPausePanel->PressButton();
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->PressButton();
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->PressButton();
		break;
	default:
		break;
	}
}

void
GUIManager::PressButton(Game::GameState state, int x, int y)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->CheckButtonsPressed(x, y);
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->CheckButtonsPressed(x, y);
		break;
	case Game::GameState::GamePlay:
		break;
	case Game::GameState::Win:
		m_pWinPanel->CheckButtonsPressed(x, y);
		break;
	case Game::GameState::Lose:
		m_pLosePanel->CheckButtonsPressed(x, y);
		break;
	case Game::GameState::Pause:
		m_pPausePanel->CheckButtonsPressed(x, y);
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->CheckButtonsPressed(x, y);
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->CheckButtonsPressed(x, y);
		break;
	default:
		break;
	}
}

void
GUIManager::HoverOnButton(Game::GameState state, int x, int y)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->CheckButtonsHovered(x, y);
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->CheckButtonsHovered(x, y);
		break;
	case Game::GameState::GamePlay:
		break;
	case Game::GameState::Win:
		m_pWinPanel->CheckButtonsHovered(x, y);
		break;
	case Game::GameState::Lose:
		m_pLosePanel->CheckButtonsHovered(x, y);
		break;
	case Game::GameState::Pause:
		m_pPausePanel->CheckButtonsHovered(x, y);
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->CheckButtonsHovered(x, y);
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->CheckButtonsHovered(x, y);
		break;
	default:
		break;
	}
}

void
GUIManager::ResetButtons(Game::GameState state)
{
	switch (state)
	{
	case Game::GameState::SplashScreen:
		break;
	case Game::GameState::MainMenu:
		m_pMainMenuPanel->ResetButtons();
		break;
	case Game::GameState::ChooseLevel:
		m_pLevelChooserPanel->ResetButtons();
		break;
	case Game::GameState::GamePlay:
		break;
	case Game::GameState::Win:
		m_pWinPanel->ResetButtons();
		break;
	case Game::GameState::Lose:
		m_pLosePanel->ResetButtons();
		break;
	case Game::GameState::Pause:
		m_pPausePanel->ResetButtons();
		break;
	case Game::GameState::Debug:
		m_pDebuggingPanel->ResetButtons();
		break;
	case Game::GameState::Instruction:
		m_pInstructionPanel->ResetButtons();
		break;
	default:
		break;
	}
}