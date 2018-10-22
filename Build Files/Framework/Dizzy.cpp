#include "Dizzy.h"
#include "AnimatedSprite.h"

//constants
const int width = 64;

Dizzy::Dizzy()
	: Entity()
{

}

Dizzy::Dizzy(float x, float y, int width, int height)
: Entity(x, y, width, height)
{

}

Dizzy::~Dizzy()
{
	Entity::~Entity();

	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

bool
Dizzy::Initialise(AnimatedSprite* sprite)
{
	m_pAnimatedSprite = sprite;

	return (true);
}

void
Dizzy::Process(float deltaTime)
{
	if (m_pAnimatedSprite)
	{
		m_pAnimatedSprite->Process(deltaTime);

		m_pAnimatedSprite->SetX(static_cast<int>(m_x));
		m_pAnimatedSprite->SetY(static_cast<int>(m_y));
	}
}

void
Dizzy::Draw(BackBuffer& backBuffer)
{
 	m_pAnimatedSprite->Draw(backBuffer, m_width);
}

void
Dizzy::AddFrames(int width, int frameCounts, float speed)
{
	if (m_pAnimatedSprite)
	{
		for (int i = 0; i < frameCounts; ++i)
		{
			m_pAnimatedSprite->AddFrame(i * width);
		}
	}

	m_pAnimatedSprite->SetFrameWidth(width);
	m_pAnimatedSprite->SetFrameSpeed(speed);
}

void
Dizzy::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Dizzy::StartAnimating()
{
	m_pAnimatedSprite->StartAnimating();
}