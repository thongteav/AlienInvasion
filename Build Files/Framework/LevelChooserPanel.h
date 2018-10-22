#pragma once

#ifndef __LEVEL_CHOOSER_PANEL_H__
#define __LEVEL_CHOOSER_PANEL_H__

// Local includes:
#include "Panel.h"

class LevelChooserPanel : public Panel
{
	// Member Functions:
public:
	LevelChooserPanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);
};

#endif // !__LEVEL_CHOOSER_PANEL_H__
