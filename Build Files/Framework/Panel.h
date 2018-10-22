#pragma once

#ifndef __PANEL_H__
#define __PANEL_H__

// Local includes:
#include "GUIComponent.h"
#include "BackBuffer.h"
#include "Label.h"
#include "Button.h"
#include "Game.h"

// Library includes:
#include <vector>

class Panel : public GUIComponent
{
	// Member Methods:
public:
	Panel();
	Panel(int x, int y, int width, int height);
	~Panel();

	virtual void Initialise(BackBuffer& backbuffer) = 0;

	void DeleteLabels();
	void DeleteButtons();

	void ProcessGameState(Game& game);

	void Draw(BackBuffer& backBuffer);
	virtual void DrawLabels(BackBuffer& backBuffer);
	void DrawButtons(BackBuffer& backBuffer);

	void AddLabel(Label* label);
	void AddButton(Button* button);

	bool CheckButtonsPressed(int x, int y);
	bool CheckButtonsHovered(int x, int y);

	void PreviousButton();
	void NextButton();

	void PressButton();

	void ResetButtons();

protected:

private:

	// Member Fields:
public:

protected:
	std::vector<Label*> m_pLabels;
	std::vector<Button*> m_pButtons;

	int m_currentBtn;

private:

};

#endif // !__PANEL_H__
