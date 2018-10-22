#pragma once

#ifndef __POWER_UP_H__
#define __POWER_UP_H__

// Local includes:
#include "Entity.h"

class PowerUp : public Entity
{
	// Member Functions
public:
	PowerUp();
	PowerUp(float x, float y, int width, int height);

	void Draw(BackBuffer& backBuffer);
	void CheckBoundary();

protected:

private:

	// Member Fields
public:

protected:
	
private:

};

#endif // !__POWER_UP_H__

