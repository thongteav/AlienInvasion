#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

// Local includes:
#include "GUIComponent.h"

// Library includes:
#include <string>

class Button : public GUIComponent
{
	// Member Methods:
public:
	Button();
	Button(int x, int y, int width, int height, std::string text);

	void Draw(BackBuffer& backBuffer);

	void Toggle();
	void SetHighlighted(bool highlighted);
	void SetPressed(bool pressed);
	void SetDebugginig(bool debug);
	void SetSelected(bool selected);
	
	bool IsPressed(int x, int y);
	bool IsHovered(int x, int y);
	bool IsHighlighted();
	bool IsPressed();
	bool IsSelected();

protected:
	bool IsOnButton(int x, int y);

private:

	// Member Fields:
public:

protected:

private:
	std::string m_text;

	bool m_pressed;
	bool m_highlighted;
	bool m_selected;
	bool m_debugging;
};

#endif // !__BUTTON_H__
