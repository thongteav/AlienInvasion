#pragma once

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// Local includes:
#include "Entity.h"

class Particle : public Entity
{
	// Member Methods:
public:
	Particle();
	Particle(float x, float y, int width, int height);
	~Particle();

	void Process(float deltaTime);

protected:

private:

	// Member Fields:
public:

protected:

private:

};

#endif // !__PARTICLE_H__
