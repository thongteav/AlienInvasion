// This include:
#include "GUIComponent.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"

// Library includes:
#include <cassert>

GUIComponent::GUIComponent()
: m_x(0)
, m_y(0)
, m_width(0)
, m_height(0)
, m_pSprite(0)
, m_drawBackground(false)
, m_r(128)
, m_g(128)
, m_b(128)
, m_a(128)
, m_textRed(0)
, m_textGreen(0)
, m_textBlue(0)
{

}

GUIComponent::GUIComponent(int x, int y, int width, int height)
: m_x(x)
, m_y(y)
, m_width(width)
, m_height(height)
, m_pSprite(0)
, m_drawBackground(false)
, m_r(128)
, m_g(128)
, m_b(128)
, m_a(128)
, m_textRed(0)
, m_textGreen(0)
, m_textBlue(0)
{

}

GUIComponent::~GUIComponent()
{
	if (m_pSprite)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
}

bool
GUIComponent::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void
GUIComponent::Draw(BackBuffer& backBuffer)
{
	if (m_pSprite)
	{
		m_pSprite->SetX(m_x);
		m_pSprite->SetY(m_y);
		backBuffer.DrawSprite(*m_pSprite, m_width, m_height);
	}
	else
	{
		if (m_drawBackground)
		{
			backBuffer.SetDrawColour(m_r, m_g, m_b, m_a);
			backBuffer.DrawFilledRectangle(m_x, m_y, m_width, m_height);
		}
	}
}

void
GUIComponent::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void
GUIComponent::SetDimension(int width, int height)
{
	m_width = width;
	m_height = height;
}

void
GUIComponent::SetPositionX(int x)
{
	m_x = x;
}

void
GUIComponent::SetPosiitionY(int y)
{
	m_y = y;
}

void
GUIComponent::SetWidth(int width)
{
	m_width = width;
}

void
GUIComponent::SetHeight(int height)
{
	m_height = height;
}

void
GUIComponent::SetDrawBackground(bool draw)
{
	m_drawBackground = draw;
}

void
GUIComponent::SetBackgroundColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void
GUIComponent::SetTextColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_textRed = r;
	m_textGreen = g;
	m_textBlue = b;
}

int
GUIComponent::GetPositionX()
{
	return (m_x);
}

int
GUIComponent::GetPositionY()
{
	return (m_y);
}

int
GUIComponent::GetWidth()
{
	return (m_width);
}

int
GUIComponent::GetHeight()
{
	return (m_height);
}