// COMP710 GP 2D Framework 2018

// This includes:
#include "Game.h"

// Local includes:
#include "BackBuffer.h"
#include "InputHandler.h"
#include "LogManager.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "SpriteSheet.h"
#include "Paddle.h"
#include "Ball.h"
#include "Entity.h"
#include "Button.h"
#include "HUD.h"
#include "IcePowerUp.h"
#include "IceField.h"
#include "BallTrail.h"
#include "SoundManager.h"
#include "GUIManager.h"
#include "LevelManager.h"
#include "ParticleEmitter.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

// Static Members:
Game* Game::sm_pInstance = 0;

// constants
const int Game::WIDTH = 800;
const int Game::HEIGHT = 600;
const int CENTER_X = Game::WIDTH / 2;
const int CENTER_Y = Game::HEIGHT/2;

const float PADDLE_SPEED = 300;
const float BALL_FULL_SPEED = 400;
const int BALL_SIZE = 16;
const float SPEED_REDUCE_CONSTANT = 4;

const int PLAYER_MAX_LIVES = 3;

const float PADDLE_INIT_Y = static_cast<float>(Game::HEIGHT / 8 * 7);
const float BALL_INIT_Y = static_cast<float>(PADDLE_INIT_Y - BALL_SIZE);

const float FIELD_INIT_Y = PADDLE_INIT_Y - 120;
const int FIELD_HEIGHT = 100;
const float FIELD_MAX_AGE = 15.0f;

const int POWER_UP_SIZE = 32;
const float POWER_UP_SPEED = 100;

const int TRAIL_NUM = 5;
const int TRAIL_SIZE = BALL_SIZE / 2;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_pPaddle(0)
, m_pBall(0)
, m_lives(PLAYER_MAX_LIVES)
, m_pHUD(0)
, m_pIcePowerUps(0)
, m_pIceField(0)
, m_pBallTrails(0)
, m_pSoundManager(0)
, m_pGUIManager(0)
, m_pLevelManager(0)
{
	srand(static_cast<unsigned int>(time(0)));
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	// delete game entities
	delete m_pPaddle;
	m_pPaddle = 0;

	delete m_pBall;
	m_pBall = 0;

	delete m_pHUD;
	m_pHUD = 0;

	delete m_pGUIManager;
	m_pGUIManager = 0;

	delete m_pIceField;
	m_pIceField = 0;

	delete m_pLevelManager;
	m_pLevelManager = 0;

	delete m_pSoundManager;
	m_pSoundManager = 0;

	DeletePowerUps();
	DeleteBallTrails();
}

void
Game::DeletePowerUps()
{
	std::vector<IcePowerUp*>::iterator iterIce;
	iterIce = m_pIcePowerUps.begin();

	while (iterIce != m_pIcePowerUps.end())
	{
		delete (*iterIce);
		*iterIce = 0;
		iterIce = m_pIcePowerUps.erase(iterIce);
	}
}

void
Game::DeleteBallTrails()
{
	std::vector<BallTrail*>::iterator iterTrail;
	iterTrail = m_pBallTrails.begin();

	while (iterTrail != m_pBallTrails.end())
	{
		delete (*iterTrail);
		*iterTrail = 0;
		iterTrail = m_pBallTrails.erase(iterTrail);
	}
}

bool
Game::Initialise()
{
	srand(static_cast<unsigned int>(0));

	//Initial game state
	m_currentState = GameState::SplashScreen;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(WIDTH, HEIGHT))
	{
		LogManager::GetInstance().Log("BackBuffer Init Failed!");
		return (false);
	}
	m_pBackBuffer->SetClearColour(16, 29, 46);

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!ed");
		return (false);
	}

	SpawnPaddle(static_cast<float>(CENTER_X), PADDLE_INIT_Y);
	SpawnBall(static_cast<float>(CENTER_X), BALL_INIT_Y);
	SpawnIceField();
	SpawnBallTrails(TRAIL_NUM);

	m_pLevelManager = new LevelManager();
	m_pLevelManager->Initialise(*m_pBackBuffer);
	m_pLevelManager->SetLevel(1);
	m_pLevelManager->StartLevel();

	m_pHUD = new HUD();
	m_pHUD->Initialise(*m_pBackBuffer);

	m_pGUIManager = new GUIManager();
	m_pGUIManager->Initialise(*m_pBackBuffer);

	m_pSoundManager = new SoundManager();
	m_pSoundManager->Initialise();
	
	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}

		std::string msg = "FPS: " + std::to_string(m_FPS);
		LogManager::GetInstance().Debug(msg.c_str());

		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	m_pGUIManager->Process(m_currentState, deltaTime);
	m_pGUIManager->ProcessGameState(m_currentState, *this);
	ProcessGamePlayState(deltaTime);
}

void
Game::ProcessGamePlayState(float deltaTime)
{
	if (m_currentState == GameState::GamePlay)
	{
		ProcessGamePlay(deltaTime);

		if (m_lives <= 0)
		{
			SetGameState(GameState::Lose);
		}

		if (m_pLevelManager->IsLevelCompleted())
		{
			SetGameState(GameState::Win);
		}
	}
}

void
Game::ProcessGamePlay(float deltaTime)
{
	m_pLevelManager->Process(deltaTime);

	m_pPaddle->Process(deltaTime);

	m_pLevelManager->IsBossAttackHitPaddle(*m_pPaddle);

	m_pHUD->SetPlayerLives(m_lives);

	if (!m_pBall->IsDead())
	{
		if (!m_pBall->IsMoving())
		{
			ProcessBallTrails(deltaTime);
		}

		m_pBall->Process(deltaTime);

		float velocityX = m_pBall->GetHorizontalVelocity();
		float velocityY = m_pBall->GetVerticalVelocity();

		bool fast = false;
		if (abs(velocityX) == BALL_FULL_SPEED || abs(velocityY) == BALL_FULL_SPEED)
		{
			fast = true;
		}
		if (!m_pIceField->IsDead())
		{
			bool collided = m_pIceField->IsCollidingWith(*m_pBall);

			if (collided && fast)
			{
				m_pBall->SetHorizontalVelocity(velocityX / SPEED_REDUCE_CONSTANT);
				m_pBall->SetVerticalVelocity(velocityY / SPEED_REDUCE_CONSTANT);
			}
			else if (!collided && !fast)
			{
				m_pBall->SetHorizontalVelocity(velocityX * SPEED_REDUCE_CONSTANT);
				m_pBall->SetVerticalVelocity(velocityY * SPEED_REDUCE_CONSTANT);
			}
		}
		else
		{
			if (!fast)
			{
				m_pBall->SetHorizontalVelocity(velocityX * SPEED_REDUCE_CONSTANT);
				m_pBall->SetVerticalVelocity(velocityY * SPEED_REDUCE_CONSTANT);
			}
		}

		// Check ball collision with other objects
		if (m_pBall->IsCollidingWith(*m_pPaddle, deltaTime))
		{
			m_pBall->BounceOffPaddle(*m_pPaddle);
		}

		m_pLevelManager->IsBossHitByBall(*m_pBall, deltaTime);
	}
	else
	{
		ResetBallPaddle();
		--m_lives;
	}
	
	m_pLevelManager->IsEnemyHitByBall(*m_pBall, deltaTime);
	m_pLevelManager->IsBlockHitByBall(*m_pBall, deltaTime);

	std::vector<IcePowerUp*>::iterator iterIce;
	iterIce = m_pIcePowerUps.begin();

	while (iterIce != m_pIcePowerUps.end())
	{
		(*iterIce)->Process(deltaTime);

		if ((*iterIce)->IsCollidingWith(*m_pPaddle))
		{
			((*iterIce))->SetDead(true);
			SpawnIceField();
		}

		++iterIce;
	}

	iterIce = m_pIcePowerUps.begin();
	while (iterIce != m_pIcePowerUps.end())
	{
		if ((*iterIce)->IsDead())
		{
			delete (*iterIce);
			*iterIce = 0;
			iterIce = m_pIcePowerUps.erase(iterIce);
		}
		else
		{
			++iterIce;
		}
	}

	//m_pIceField->SetDead(false);
	m_pIceField->Process(deltaTime);
}

void
Game::ProcessBallTrails(float deltaTime)
{
	if (!m_pBall->IsMoving())
	{
		double ballAngle = m_pBall->GetAngle();
		std::string msg = "Ball angle: " + std::to_string(ballAngle);
		LogManager::GetInstance().Debug(msg.c_str());

		std::vector<BallTrail*>::iterator iterTrail;
		iterTrail = m_pBallTrails.begin();

		while (iterTrail != m_pBallTrails.end())
		{
			(*iterTrail)->SetAngle(ballAngle);
			(*iterTrail)->Process(deltaTime);
			++iterTrail;
		}
	}
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	if (m_currentState == GameState::GamePlay ||
		m_currentState == GameState::Win ||
		m_currentState == GameState::Lose ||
		m_currentState == GameState::Pause ||
		m_currentState == GameState::Debug)
	{
		DrawGamePlay(backBuffer);
	}

	m_pGUIManager->Draw(m_currentState, backBuffer);

	backBuffer.Present();
}

void
Game::DrawBallTrails(BackBuffer& backBuffer)
{
	if (!m_pBall->IsMoving())
	{
		std::vector<BallTrail*>::iterator iterTrail;
		iterTrail = m_pBallTrails.begin();

		while (iterTrail != m_pBallTrails.end())
		{
			(*iterTrail)->Draw(backBuffer);
			++iterTrail;
		}
	}
}

void
Game::DrawGamePlay(BackBuffer& backBuffer)
{
	m_pLevelManager->Draw(backBuffer);

	m_pPaddle->Draw(backBuffer);

	m_pBall->Draw(backBuffer);
	DrawBallTrails(backBuffer);

	std::vector<IcePowerUp*>::iterator iterIce;
	iterIce = m_pIcePowerUps.begin();

	while (iterIce != m_pIcePowerUps.end())
	{
		(*iterIce)->Draw(backBuffer);
		++iterIce;
	}

	m_pIceField->Draw(backBuffer);

	m_pHUD->Draw(backBuffer);

	PrintDebugInfo(backBuffer);
}

void
Game::Quit()
{
	m_looping = false;
}

void
Game::PrintDebugInfo(BackBuffer& backBuffer)
{
	if (LogManager::GetInstance().IsDebugging())
	{
		std::vector<std::string> messages;
		messages.push_back("Ball x pos: " + std::to_string(m_pBall->GetPositionX()));
		messages.push_back("Ball y pos: " + std::to_string(m_pBall->GetPositionY()));
		messages.push_back("Ball speed x: " + std::to_string(m_pBall->GetHorizontalVelocity()));
		messages.push_back("Ball speed y: " + std::to_string(m_pBall->GetVerticalVelocity()));

		backBuffer.SetTextColour(255, 0, 0);

		std::vector<std::string>::iterator msgIter;
		msgIter = messages.begin();

		int count = 0;
		int x = 50;
		int y = 400;
		int offset = 20;

		while (msgIter != messages.end())
		{
			backBuffer.DrawText(x, y + offset * count, (*msgIter).c_str());
			++msgIter;
			++count;
		}
	}	
}

// Spawn entities
void
Game::SpawnPaddle(float x, float y)
{
	Sprite* pPaddleSprite = 0;
	pPaddleSprite =	m_pBackBuffer->CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\paddle-normal.png");

	int width = pPaddleSprite->GetWidth();
	int height = pPaddleSprite->GetHeight();
	m_pPaddle = new Paddle(x - width/2, y, width, height);
	m_pPaddle->Initialise(pPaddleSprite);
}

void
Game::SpawnBall(float x, float y)
{
	Sprite* pBallSprite = 0;
	pBallSprite = m_pBackBuffer->CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\ball-16.png");

	int width = pBallSprite->GetWidth();
	int height = pBallSprite->GetHeight();
	m_pBall = new Ball(x - width / 2, y, width, height);
	m_pBall->Initialise(pBallSprite);
	m_pBall->SetAngle(90);
}

// Movements
void 
Game::MovePaddleLeft()
{
	if (m_pBall->IsMoving())
	{
		m_pPaddle->SetHorizontalVelocity(-PADDLE_SPEED);
	}
}

void 
Game::MovePaddleRight()
{
	if (m_pBall->IsMoving())
	{
		m_pPaddle->SetHorizontalVelocity(PADDLE_SPEED);
	}
}

void 
Game::StopPaddle()
{
	m_pPaddle->SetHorizontalVelocity(0);
}

void 
Game::ShootBall()
{
	if (!m_pBall->IsMoving())
	{
		m_pBall->SetHorizontalVelocity(BALL_FULL_SPEED);
		m_pBall->SetVerticalVelocity(-BALL_FULL_SPEED);

		m_pSoundManager->PlaySound(SoundManager::SoundEfx::SHOOT);
	}
}

void
Game::MoveShootDirectionAntiClockwise()
{
	if (!m_pBall->IsMoving())
	{
		m_pBall->MoveAngleClockwise();
	}
}

void
Game::MoveShootDirectionClockwise()
{
	if (!m_pBall->IsMoving())
	{
		m_pBall->MoveAngleAntiClockwise();
	}
}

void
Game::SpawnIceField()
{
	if (!m_pIceField)
	{
		Sprite* pSprite = 0;
		//pSprite = m_pBackBuffer->CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\ice.png");

		m_pIceField = new IceField(0.0f, FIELD_INIT_Y, WIDTH, FIELD_HEIGHT, FIELD_MAX_AGE);
		m_pIceField->SetDead(true);
		//m_pIceField->Initialise(pSprite);
	}
	else
	{
		m_pIceField->Restart();
	}	
}

void
Game::SpawnIcePowerUp(float x, float y)
{
	int chance = GetRandomNumber(100, 0);
	if (chance < 40)
	{
		Sprite* pSprite = 0;
		pSprite = m_pBackBuffer->CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\ice.png");

		IcePowerUp* ice = 0;
		ice = new IcePowerUp(x, y, POWER_UP_SIZE, POWER_UP_SIZE);
		ice->Initialise(pSprite);
		ice->SetVerticalVelocity(POWER_UP_SPEED);

		m_pIcePowerUps.push_back(ice);
	}	
}

void
Game::SpawnBallTrails(int count)
{
	float offsetY = 20;
	for (int i = 0; i < count; ++i)
	{
		Sprite* pSprite = 0;
		pSprite = m_pBackBuffer->CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\grey_circle.png");

		BallTrail* trail = 0;
		trail = new BallTrail(static_cast<float>(CENTER_X - TRAIL_SIZE / 2), BALL_INIT_Y, TRAIL_SIZE, TRAIL_SIZE, static_cast<float>(-offsetY * (i + 1)));
		trail->Initialise(pSprite);

		m_pBallTrails.push_back(trail);
	}
}

void
Game::RestartLevel()
{
	//Reset the whole level
	ResetBallPaddle();
	ResetLives();
	DeletePowerUps();
	m_pIceField->SetDead(true);
	m_pLevelManager->RestartLevel();
}

void
Game::NextLevel()
{
	m_pLevelManager->NextLevel();
	m_pLevelManager->StartLevel();
}

void
Game::SetLevel(int level)
{
	m_pLevelManager->SetLevel(level);
	m_pLevelManager->StartLevel();
}

void
Game::ResetBallPaddle()
{
	m_pBall->Reset();
	m_pPaddle->SetPositionX(static_cast<float>(CENTER_X - (m_pPaddle->GetWidth() / 2)));
	m_pPaddle->SetPositionY(PADDLE_INIT_Y);
	m_pPaddle->SetDizzy(false);
}

void
Game::ResetLives()
{
	m_lives = PLAYER_MAX_LIVES;
}

void
Game::PressButton(int x, int y)
{
	m_pGUIManager->PressButton(m_currentState, x, y);
}

void
Game::HoverOnButton(int x, int y)
{
	m_pGUIManager->HoverOnButton(m_currentState, x, y);
}

void
Game::SetGameState(GameState newState)
{
	GameState prevState = m_currentState;
	m_currentState = newState;

	//action to exit from prev state
	ExitGameState(prevState);

	//action to enter a new state
	EnterGameState(newState, prevState);
}

void
Game::EnterGameState(GameState enterState, GameState exitState)
{
	m_pGUIManager->ResetButtons(enterState);

	switch (enterState)
	{
		case Game::GameState::SplashScreen:
			break;
		case Game::GameState::MainMenu:
			break;
		case Game::GameState::Instruction:
			break;
		case Game::GameState::ChooseLevel:
			break;
		case Game::GameState::GamePlay:
			if (exitState != GameState::Pause && exitState!= GameState::Debug)
			{
				RestartLevel();
			}
			break;
		case Game::GameState::Win:
			m_pSoundManager->PlaySound(SoundManager::SoundEfx::SUCCESS);
			break;
		case Game::GameState::Lose:
			m_pHUD->SetPlayerLives(m_lives);
			m_pSoundManager->PlaySound(SoundManager::SoundEfx::FAIL);
			break;
		case Game::GameState::Pause:
			break;
		case Game::GameState::Debug:
			break;
		default:
			break;
	}
}

void
Game::ExitGameState(GameState exitState)
{
	switch (exitState)
	{
		case Game::GameState::SplashScreen:
			break;
		case Game::GameState::MainMenu:
			break;
		case Game::GameState::Instruction:
			break;
		case Game::GameState::ChooseLevel:
			break;
		case Game::GameState::GamePlay:
			break;
		case Game::GameState::Win:
			break;
		case Game::GameState::Lose:
			break;
		case Game::GameState::Pause:
			break;
		case Game::GameState::Debug:
			break;
		default:
			break;
	}
}

void
Game::NextButton()
{
	m_pGUIManager->NextButton(m_currentState);
}

void
Game::PreviousButton()
{
	m_pGUIManager->PreviousButton(m_currentState);
}

void
Game::PressButton()
{
	m_pGUIManager->PressButton(m_currentState);
}

void
Game::Pause()
{
	if (m_currentState == GameState::GamePlay)
	{
		SetGameState(GameState::Pause);
	}
}

void
Game::ShowDebugMenu()
{
	if (m_currentState == GameState::GamePlay)
	{
		SetGameState(GameState::Debug);
	}
}

int
Game::GetRandomNumber(int range, int base)
{
	return rand() % range + base;
}

Paddle*
Game::GetPaddle()
{
	return (m_pPaddle);
}

Level*
Game::GetLevel()
{
	return (m_pLevelManager->GetLevel());
}