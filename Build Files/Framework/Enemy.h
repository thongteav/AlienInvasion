#pragma once

#ifndef __ENEMY_H__
#define __ENEMY_H__

// Local includes:
#include "Entity.h"
#include "SpriteSheet.h"

class Enemy : public Entity
{
public:
	enum Status
	{
		STAND,
		HURT,
		DEAD,
		STATUS_MODES
	};

	// Member Methods:
public:
	Enemy();
	Enemy(float x, float y, int width, int height);
	~Enemy();

	bool Initialise(SpriteSheet* spritesheet);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void NextStatus();
	void Revive();
	Enemy::Status GetStatus();

protected:

private:

	// Member Fields:
public:
	enum Colour
	{
		GRAY,
		BLUE,
		GREEN,
		PINK,
		YELLOW,
		COLOUR_SIZE
	};

protected:
	SpriteSheet* m_pSpriteSheet;
	Colour m_colour;
	Status m_status;

private:
	
};

#endif // !__ENEMY_H__

