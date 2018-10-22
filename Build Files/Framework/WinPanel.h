#pragma once

#ifndef __WIN_PANEL_H__
#define __WIN_PANEL_H__

// Local includes:
#include "Panel.h"

class WinPanel : public Panel
{
	// Member Functions:
public:
	WinPanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__WIN_PANEL_H__
