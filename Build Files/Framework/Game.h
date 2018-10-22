// COMP710 GP 2D Framework 2018
#pragma once

#ifndef __GAME_H__
#define __GAME_H__

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Paddle;
class Ball;
class Entity;
class Button;
class HUD;
class IcePowerUp;
class IceField;
class BallTrail;
class GreenBoss;
class PinkBoss;
class SoundManager;
class GUIManager;
class LevelManager;
class Level;

// Library includes:
#include <vector>
#include <cstdlib>
#include <ctime>

class Game
{
	// Member Methods:
	public:
		enum class GameState
		{
			SplashScreen,
			MainMenu,
			Instruction,
			ChooseLevel,
			GamePlay,
			Win,
			Lose,
			Pause,
			Debug
		};

		static Game& GetInstance();
		static void DestroyInstance();
		~Game();

		void DeleteEnemies();
		void DeleteBlocks();
		void DeletePowerUps();
		void DeleteBallTrails();

		bool Initialise();
		bool DoGameLoop();
		void Quit();

		void MovePaddleLeft();
		void MovePaddleRight();
		void StopPaddle();
		void ShootBall();
		void MoveShootDirectionClockwise();
		void MoveShootDirectionAntiClockwise();

		// Spawning entities
		void SpawnPaddle(float x, float y);
		void SpawnBall(float x, float y);
		void SpawnIcePowerUp(float x, float y);
		void SpawnIceField();
		void SpawnBallTrails(int count);

		void RestartLevel();
		void NextLevel();
		void SetLevel(int level);

		// Reset game
		void ResetBallPaddle();
		void ResetLives();

		void PressButton(int x, int y);
		void HoverOnButton(int x, int y);

		void PreviousButton();
		void NextButton();
		void PressButton();

		void PrintDebugInfo(BackBuffer& backBuffer);

		void SetGameState(GameState enterState);

		void EnterGameState(GameState enterState, GameState exitState);
		void ExitGameState(GameState exitState);

		void Pause();
		void ShowDebugMenu();
		int GetRandomNumber(int range, int base);

		Paddle* GetPaddle();
		Level* GetLevel();

	protected:
		void Process(float deltaTime);
		void Draw(BackBuffer& backBuffer);

		void ProcessGamePlayState(float deltaTime);
		void ProcessGamePlay(float deltaTime);
		void DrawGamePlay(BackBuffer& backBuffer);

		void ProcessBallTrails(float deltaTime);

		void DrawBallTrails(BackBuffer& backBuffer);

	private:
		Game(const Game& game);
		Game& operator=(const Game& game);

		Game();

	// Member Fields:
	public:
		static const int WIDTH;
		static const int HEIGHT;

	protected:
		static Game* sm_pInstance;
		BackBuffer* m_pBackBuffer;
		InputHandler* m_pInputHandler;
		bool m_looping;

		SoundManager* m_pSoundManager;
		LevelManager* m_pLevelManager;
		GUIManager* m_pGUIManager;
		HUD* m_pHUD;
		 
		// Simulation Counters:
		float m_elapsedSeconds;
		float m_lag;
		float m_executionTime;
		int m_lastTime;
		int m_frameCount;
		int m_FPS;
		int m_numUpdates;
		bool m_drawDebugInfo;

		// Game Entities:
		Paddle* m_pPaddle;
		Ball* m_pBall;
		IceField* m_pIceField;
		std::vector<IcePowerUp*> m_pIcePowerUps;
		std::vector<BallTrail*> m_pBallTrails;

		int m_lives;

		GameState m_currentState;

	private:		

};

#endif // !__GAME_H__
