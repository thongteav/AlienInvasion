#pragma once

#ifndef __BLOCK_H__
#define __BLOCK_H__

// Local includes:
#include "Entity.h"
#include "BackBuffer.h"

class Block : public Entity
{
	// Memeber Functions
public:
	Block();
	Block(float x, float y, int width, int height);

	void Update(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	// Member Fields
public:

protected:

private:

};

#endif // !__BLOCK_H__
