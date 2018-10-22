#pragma once

#ifndef __PAUSE_PANEL_H__
#define __PAUSE_PANEL_H__

// Local includes:
#include "Panel.h"

class PausePanel : public Panel
{
	// Member Functions:
public:
	PausePanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__PAUSE_PANEL_H__
