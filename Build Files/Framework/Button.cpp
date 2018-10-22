// This include:
#include "Button.h"

// Local includes:
#include "GUIComponent.h"
#include "BackBuffer.h"
#include "Sprite.h"

// Library includes:
#include <string>

Button::Button()
: GUIComponent()
, m_pressed(false)
, m_highlighted(false)
, m_selected(false)
, m_debugging(false)
{
	GUIComponent::SetBackgroundColour(255, 202, 24, 255);
}

Button::Button(int x, int y, int width, int height, std::string text)
: GUIComponent(x, y, width, height)
, m_text(text)
, m_pressed(false)
, m_highlighted(false)
, m_selected(false)
, m_debugging(false)
{
	GUIComponent::SetBackgroundColour(255, 202, 24, 255);
}

void
Button::Draw(BackBuffer& backBuffer)
{
	if (!m_pSprite)
	{
		if (m_highlighted)
		{
			backBuffer.SetDrawColour(255, 255, 255);
			int offset = 3;
			backBuffer.DrawRectangle(m_x, m_y, m_width, m_height, offset);

			//revert the colours
			unsigned char r = 255 - m_r;
			unsigned char g = 255 - m_g;
			unsigned char b = 255 - m_b;
			unsigned char text_r = 255 - m_textRed;
			unsigned char text_g = 255 - m_textGreen;
			unsigned char text_b = 255 - m_textBlue;

			backBuffer.SetDrawColour(r, g, b, m_a);
			backBuffer.SetTextColour(text_r, text_g, text_b);
		}
		else
		{
			backBuffer.SetDrawColour(m_r, m_g, m_b, m_a);
			backBuffer.SetTextColour(m_textRed, m_textGreen, m_textBlue);
		}

		std::string myText = m_text;
		if (m_debugging)
		{
			if (m_selected)
			{
				backBuffer.SetTextColour(255, 0, 0);
				myText += ": OFF";
			}
			else
			{
				backBuffer.SetTextColour(0, 255, 0);
				myText += ": ON";
			}
			backBuffer.SetDrawColour(0, 0, 0);
		}

		backBuffer.DrawFilledRectangle(m_x, m_y, m_width, m_height);
		backBuffer.DrawText(m_x, m_y, m_width, m_height, myText.c_str());
	}
	else
	{
		backBuffer.DrawSprite(*m_pSprite);
	}
	
}

void
Button::Toggle()
{
	m_pressed = !m_pressed;
}

void
Button::SetPressed(bool pressed)
{
	m_pressed = pressed;
}

void
Button::SetHighlighted(bool highlighted)
{
	m_highlighted = highlighted;
}

void
Button::SetDebugginig(bool debug)
{
	m_debugging = debug;
}

void
Button::SetSelected(bool selected)
{
	m_selected = selected;
}

bool
Button::IsPressed(int x, int y)
{
	bool pressed = false;
	pressed = IsOnButton(x, y);

	return (pressed);
}

bool
Button::IsPressed()
{
	return (m_pressed);
}

bool
Button::IsHovered(int x, int y)
{
	bool hovered = false;
	hovered = IsOnButton(x, y);

	return (hovered);
}

bool
Button::IsOnButton(int x, int y)
{
	bool xIntersected = x >= m_x && x <= m_x + m_width;
	bool yIntersected = y >= m_y && y <= m_y + m_height;

	return (xIntersected && yIntersected);
}

bool
Button::IsHighlighted()
{
	return (m_highlighted);
}

bool
Button::IsSelected()
{
	return (m_selected);
}