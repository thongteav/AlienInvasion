#pragma once

#ifndef __SPLASH_SCREEN_PANEL_H__
#define __SPLASH_SCREEN_PANEL_H__

// Local includes:
#include "Panel.h"

class SplashScreenPanel : public Panel
{
	// Member Functions:
public:
	SplashScreenPanel();

	void Initialise(BackBuffer& backBuffer);

	void ProcessGameState(Game& game);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:
	float Lerp(float initial, float final, float difference);

	// Member Fields:
public:

protected:

private:
	float m_totalEllapsedTime;
	bool m_animating;
};

#endif // !__SPLASH_SCREEN_PANEL_H__
