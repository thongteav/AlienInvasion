// This include:
#include "AnimatedSprite.h"

// Local includes:
#include "Texture.h"
#include "BackBuffer.h"
#include "LogManager.h"

// Library includes:
#include <string>

AnimatedSprite::AnimatedSprite()
: Sprite()
, m_frameSpeed(0.0f)
, m_frameWidth(0)
, m_timeEllapsed(0.0f)
, m_currentFrame(0)
, m_paused(false)
, m_loop(false)
, m_animating(false)
, m_frames(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	m_frames.push_back(x);
}

void
AnimatedSprite::Process(float deltaTime)
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

	if (m_currentFrame >= static_cast<int>(m_frames.size()))
	{
		m_currentFrame = 0;
	}

	if (!m_loop && m_timeEllapsed == 0 && m_currentFrame == 0)
	{
		m_animating = false;
	}
}

void
AnimatedSprite::Draw(BackBuffer& backBuffer, int width)
{
	backBuffer.DrawAnimatedSprite(*this, m_frames[m_currentFrame], m_frameWidth, width);
}


void
AnimatedSprite::SetFrameSpeed(float speed)
{
	m_frameSpeed = speed;
}

void
AnimatedSprite::SetFrameWidth(int width)
{
	m_frameWidth = width;
}

void
AnimatedSprite::SetLooping(bool loop)
{
	m_loop = loop;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeEllapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}
