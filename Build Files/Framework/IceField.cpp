// This include:
#include "IceField.h"
#include "BackBuffer.h"
#include "LogManager.h"

IceField::IceField()
: Effect()
{

}

IceField::IceField(float x, float y, int width, int height)
: Effect(x, y, width, height)
{

}

IceField::IceField(float x, float y, int width, int height, float maxAge)
: Effect(x, y, width, height, maxAge)
{

}


void
IceField::Draw(BackBuffer& backBuffer)
{
	if (!m_dead)
	{
		if (m_pSprite)
		{
			Effect::DrawInDimension(backBuffer);
		}
		else
		{
			backBuffer.SetDrawColour(180, 201, 220, 180);
			backBuffer.DrawFilledRectangle(static_cast<int>(m_x), static_cast<int>(m_y), m_width, m_height);
		}
	}	
}