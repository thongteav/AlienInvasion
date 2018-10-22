#pragma once

#ifndef __HUD_H__
#define __HUD_H__

// Local includes:
#include "Panel.h"

class HUD : public Panel
{
	// Member Methods:
public:
	HUD();

	void Initialise(BackBuffer& backBuffer);
	void Draw(BackBuffer& backBuffer);
	void DrawLabels(BackBuffer& backBuffer);

	void SetPlayerLives(int lives);

protected:

private:

	// Member Fields:
public:

protected:

private:
	int m_playerLives;

};

#endif // !__HUD_H__
