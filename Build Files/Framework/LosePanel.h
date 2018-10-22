#pragma once

#ifndef __LOSE_PANEL_H__
#define __LOSE_PANEL_H__

// Local includes:
#include "Panel.h"

class LosePanel : public Panel
{
	// Member Functions:
public:
	LosePanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__LOSE_PANEL_H__
