#pragma once

#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__

// Local includes:
#include "Sprite.h"

// Forward Declarations:
class BackBuffer;
class Texture;

class SpriteSheet : public Sprite
{
	// Member Methods
public:
	SpriteSheet();
	~SpriteSheet();

	bool Initialise(Texture& texture, int frameCounts, int frameWidth, int frameHeight, bool looping);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer, int row, int col, int desWidth, int desHeight);
	void Draw(BackBuffer& backBuffer, int desWidth, int desHeight);

	int GetFrameHeight();
	int GetFrameWidth();

	void SetFrameSpeed(float speed);
	void SetFrameWidth(int width);
	void SetFrameHeight(int height);
	void SetFrameCounts(int counts);

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
	int m_frameHeight;
	int m_frameWidth;
	int m_framesPerRow;
	int m_frameCounts;
	int m_currentFrame;

	float m_frameSpeed;
	float m_timeEllapsed;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:
	
};

#endif // !__SPRITESHEET_H__
