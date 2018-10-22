// COMP710 GP 2D Framework 2018

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"

// Library includes:
#include <cassert>
#include <string>

const int DEAD_ZONE = 3500;

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		if (SDL_JoystickGetAttached(m_pGameController))
		{
			SDL_JoystickClose(m_pGameController);
			m_pGameController = 0;
		}
	}
}

bool
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

void
InputHandler::ProcessInput(Game& game)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				game.PressButton();
				game.ShootBall();
			}

			if (e.jbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				game.Pause();
			}

			if (e.jbutton.button == SDL_CONTROLLER_BUTTON_X)
			{
				game.ShowDebugMenu();
			}

			if (e.jbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				bool debug = LogManager::GetInstance().IsDebugging();
				LogManager::GetInstance().SetDebugging(!debug);

				if (debug)
				{
					LogManager::GetInstance().Log("Turning off debugging message..\n");
				}
				else
				{
					LogManager::GetInstance().Debug("Turning on debugging message..\n");
				}
			}
		}
		else if (e.type == SDL_JOYAXISMOTION)
		{
			if (e.jaxis.axis == 0)
			{
				if (e.jaxis.value < -DEAD_ZONE)
				{
					game.MovePaddleLeft();
					game.MoveShootDirectionAntiClockwise();
				}
				else if (e.jaxis.value > DEAD_ZONE)
				{
					game.MovePaddleRight();
					game.MoveShootDirectionClockwise();
				}
				else
				{
					//stop moving
					game.StopPaddle();
				}
			}			
		}
		else if (e.type == SDL_JOYHATMOTION)
		{
			std::string msg = "Value: " + std::to_string(e.jhat.value);
			LogManager::GetInstance().Debug(msg.c_str());

			if (e.jhat.value == 2)
			{
				LogManager::GetInstance().Debug("D-pad right pressed!");
				game.MovePaddleRight();
				game.MoveShootDirectionClockwise();
				game.NextButton();
			}

			if (e.jhat.value == 8)
			{
				LogManager::GetInstance().Debug("D-pad left pressed!");
				game.MovePaddleLeft();
				game.MoveShootDirectionAntiClockwise();
				game.PreviousButton();
			}

			if (e.jhat.value == 1)
			{
				LogManager::GetInstance().Debug("D-pad up pressed!");
				game.PreviousButton();
			}

			if (e.jhat.value == 4)
			{
				LogManager::GetInstance().Debug("D-pad down pressed!");
				game.NextButton();
			}

			if (e.jhat.value == 0)
			{
				game.StopPaddle();
			}
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_UP)
			{
				game.PreviousButton();
			}

			if (e.key.keysym.sym == SDLK_DOWN)
			{
				game.NextButton();
			}

			if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
			{
				LogManager::GetInstance().Debug("Enter key pressed!");
				game.PressButton();
			}

			if (e.key.keysym.sym == SDLK_LEFT)
			{
				LogManager::GetInstance().Debug("Left key pressed!");
				game.MovePaddleLeft();
				game.MoveShootDirectionAntiClockwise();
				game.PreviousButton();
			}

			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				LogManager::GetInstance().Debug("Right key pressed!");
				game.MovePaddleRight();
				game.MoveShootDirectionClockwise();
				game.NextButton();
			}

			if (e.key.keysym.sym == SDLK_SPACE)
			{
				LogManager::GetInstance().Debug("Space key pressed!");
				game.ShootBall();
			}

			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				LogManager::GetInstance().Debug("Escape key pressed!");
				game.Pause();
			}

			if (e.key.keysym.sym == SDLK_q)
			{
				LogManager::GetInstance().Debug("Q key pressed!");
				game.ShowDebugMenu();
			}

			if (e.key.keysym.sym == SDLK_b)
			{
				bool debug = LogManager::GetInstance().IsDebugging();
				LogManager::GetInstance().SetDebugging(!debug);

				if (debug)
				{
					LogManager::GetInstance().Log("Turning off debugging message..\n");
				}
				else
				{
					LogManager::GetInstance().Debug("Turning on debugging message..\n");
				}
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				LogManager::GetInstance().Debug("Left key released!");
				game.StopPaddle();
			}

			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				LogManager::GetInstance().Debug("Right key released!");
				game.StopPaddle();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				int x = e.motion.x;
				int y = e.motion.y;
				std::string msg = "x: " + std::to_string(x) + ", y: " + std::to_string(y);
				LogManager::GetInstance().Debug("Left mouse clicked!");
				LogManager::GetInstance().Debug(msg.c_str());

				game.PressButton(x, y);
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			int x = e.motion.x;
			int y = e.motion.y;

			game.HoverOnButton(x, y);
		}
	}
}
