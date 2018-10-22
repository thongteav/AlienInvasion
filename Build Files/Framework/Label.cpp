// This include:
#include "Label.h"

// Local includes:
#include "GUIComponent.h"
#include "BackBuffer.h"

// Library includes:
#include <string>

Label::Label()
: GUIComponent()
, m_text("")
{

}

Label::Label(int x, int y, int width, int height)
: GUIComponent(x, y, width, height)
, m_text("")
{

}

Label::Label(int x, int y, int width, int height, std::string text)
: GUIComponent(x, y, width, height)
, m_text(text)
{
	m_textRed = 255;
	m_textGreen = 255;
	m_textBlue = 255;
}

Label::Label(std::string text)
: GUIComponent()
, m_text(text)
{
	m_textRed = 255;
	m_textGreen = 255;
	m_textBlue = 255;
}

void
Label::Draw(BackBuffer& backBuffer)
{
	GUIComponent::Draw(backBuffer);

	if (m_text != "")
	{
		backBuffer.SetTextColour(m_textRed, m_textGreen, m_textBlue);
		backBuffer.DrawText(m_x, m_y, m_width, m_height, m_text.c_str());
	}
}

void
Label::DrawWrapped(BackBuffer& backBuffer)
{
	GUIComponent::Draw(backBuffer);

	if (m_text != "")
	{
		backBuffer.SetTextColour(m_textRed, m_textGreen, m_textBlue);
		backBuffer.DrawTextWrapped(m_x, m_y, m_width, m_height, m_text.c_str(), m_width);
	}
}

void
Label::SetText(std::string text)
{
	m_text = text;
}

