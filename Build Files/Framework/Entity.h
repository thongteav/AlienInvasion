// COMP710 GP 2D Framework 2018
#pragma once

#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;

class Entity
{
	// Member Methods:
public:
	Entity();
	Entity(float x, float y, int width, int height);
	~Entity();
	
	bool Initialise(Sprite* sprite);

	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);
	virtual void DrawInDimension(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);
	bool AABBCollision(Entity& e);
	float SweptAABBCollision(Entity& e, float& normalX, float& normalY, float deltaTime);

	bool IsMoving();

	void UpdatePosition(float deltaTime);
	void UpdatePositionWithAngle(float deltaTime);
	void CheckBoundary();

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x);

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	int GetWidth();
	int GetHeight();

	void SetWidth(int width);
	void SetHeight(int height);

	void SetAngle(double angle);
	double GetAngle() const;

	void MoveAngleClockwise();
	void MoveAngleAntiClockwise();

	float Lerp(float initial, float final, float diff);
	double ToRadian(float degree);

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	// Member Fields:
public:

protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	int m_width;
	int m_height;

	bool m_dead;

	double m_angle;

private:

};

#endif // !__ENTITY_H__
