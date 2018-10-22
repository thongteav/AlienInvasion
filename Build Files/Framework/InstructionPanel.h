#pragma once

#ifndef __INSTRUCTION_PANEL_H__
#define __INSTRUCTION_PANEL_H__

// Local includes:
#include "Panel.h"

class InstructionPanel : public Panel
{
	// Member Functions:
public:
	InstructionPanel();

	void Initialise(BackBuffer& backBuffer);
	void ProcessGameState(Game& game);

	void DrawLabels(BackBuffer& backBuffer);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__INSTRUCTION_PANEL_H__
