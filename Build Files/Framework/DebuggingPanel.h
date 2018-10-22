#pragma once

#ifndef __DEBUGGING_PANEL_H__
#define __DEBUGGING_PANEL_H__

// Local includes:
#include "Panel.h"

class DebuggingPanel : public Panel
{
	// Member Functions:
public:
	DebuggingPanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__DEBUGGING_PANEL_H__
