// This includes:
#include "Block.h"

// Local includes:
#include "BackBuffer.h"
#include "Sprite.h"

// Library includes:
#include <cassert>

Block::Block()
: Entity()
{

}

Block::Block(float x, float y, int width, int height)
: Entity(x, y, width, height)
{

}

void
Block::Update(float deltaTime)
{
	// No body implementation since block is not moving
}

void
Block::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);

	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	m_pSprite->Draw(backBuffer, m_width, m_height);
}