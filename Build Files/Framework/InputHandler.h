// COMP710 GP 2D Framework 2018
#pragma once

#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class Game;

class InputHandler
{
	// Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessInput(Game& game);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	// Member Fields:
public:

protected:
	SDL_Joystick * m_pGameController;

private:

};

#endif // !__INPUTHANDLER_H__
