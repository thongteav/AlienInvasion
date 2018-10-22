// COMP710 GP 2D Framework 2018
#pragma once

#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

// Local includes:
#include "Sprite.h"

// Library includes:
#include <vector>

// Forward Declarations:
class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Member Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer, int width);

	void SetFrameSpeed(float speed);
	void SetFrameWidth(int width);

	void Pause();
	bool IsPaused();

	void StartAnimating();
	bool IsAnimating();

	void SetLooping(bool loop);
	bool IsLooping();

protected:

private:

	// Member Fields:
public:

protected:
	std::vector<int> m_frames;

	float m_frameSpeed;
	int m_frameWidth;

	float m_timeEllapsed;
	int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // !__ANIMATEDSPRITE_H__
