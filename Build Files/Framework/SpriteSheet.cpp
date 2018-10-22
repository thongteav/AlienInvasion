// This include:
#include "SpriteSheet.h"

// Local includes:
#include "Texture.h"
#include "BackBuffer.h"

// Library includes:

SpriteSheet::SpriteSheet()
: Sprite()
, m_frameHeight(0)
, m_frameWidth(0)
, m_framesPerRow(0)
, m_frameSpeed(0.0f)
, m_timeEllapsed(0.0f)
, m_currentFrame(0)
, m_loop(false)
, m_paused(false)
, m_animating(false)
{

}

SpriteSheet::~SpriteSheet()
{

}

bool
SpriteSheet::Initialise(Texture& texture, int frameCounts, int frameWidth, int frameHeight, bool animating)
{
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	m_framesPerRow = (texture.GetWidth() / frameWidth);
	m_frameCounts = frameCounts;

	m_loop = false;
	m_paused = false;
	m_animating = animating;

	if (animating)
	{
		StartAnimating();
	}

	Sprite::Initialise(texture);

	return (true);
}

void
SpriteSheet::Process(float deltaTime)
{
	if (!m_animating)
	{
		m_paused = true;
	}

	if (!m_paused)
	{
		m_timeEllapsed += deltaTime;
	}

	if (m_timeEllapsed > m_frameSpeed)
	{
		++m_currentFrame;
		m_timeEllapsed = 0;
	}

	if (m_currentFrame >= m_frameCounts)
	{
		m_currentFrame = 0;
	}

	if (!m_loop && m_timeEllapsed == 0 && m_currentFrame == 0)
	{
		m_animating = false;
	}
}

void
SpriteSheet::Draw(BackBuffer& backBuffer, int row, int col, int desWidth, int desHeight)
{
	backBuffer.DrawSpriteSheet(*this, col * m_frameWidth, row * m_frameHeight, desWidth, desHeight);
}

void
SpriteSheet::Draw(BackBuffer& backBuffer, int desWidth, int desHeight)
{
	int row = m_currentFrame / m_frameCounts;
	int col = m_currentFrame % m_frameCounts;
	backBuffer.DrawSpriteSheet(*this, col * m_frameWidth, row * m_frameHeight, desWidth, desHeight);
}

int
SpriteSheet::GetFrameHeight()
{
	return (m_frameHeight);
}

int
SpriteSheet::GetFrameWidth()
{
	return (m_frameWidth);
}

void
SpriteSheet::SetFrameSpeed(float speed)
{
	m_frameSpeed = speed;
}

void
SpriteSheet::SetFrameWidth(int width)
{
	m_frameWidth = width;
}

void
SpriteSheet::SetFrameHeight(int height)
{
	m_frameHeight = height;
}

void
SpriteSheet::SetFrameCounts(int count)
{
	m_frameCounts = count;
}

void
SpriteSheet::SetLooping(bool loop)
{
	m_loop = loop;
}

void
SpriteSheet::Pause()
{
	m_paused = !m_paused;
}

bool
SpriteSheet::IsPaused()
{
	return (m_paused);
}

bool
SpriteSheet::IsAnimating()
{
	return (m_animating);
}

void
SpriteSheet::StartAnimating()
{
	m_animating = true;

	m_timeEllapsed = 0;
	m_currentFrame = 0;
}

bool
SpriteSheet::IsLooping()
{
	return (m_loop);
}
