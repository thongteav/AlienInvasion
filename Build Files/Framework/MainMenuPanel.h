#pragma once

#ifndef __MAIN_MENU_PANEL_H__
#define __MAIN_MENU_PANEL_H__

// Local includes:
#include "Panel.h"

class MainMenuPanel : public Panel
{
	// Member Functions:
public:
	MainMenuPanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__MAIN_MENU_PANEL_H__
