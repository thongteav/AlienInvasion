#pragma once

#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

// Local includes:
#include "BackBuffer.h"
#include "StartParticle.h"
#include "ExplosionParticle.h"

// Library includes:
#include <vector>

class ParticleEmitter
{
	// Member Methods:
public:
	ParticleEmitter();
	~ParticleEmitter();

	void DeleteStars();
	void DeleteExplosions();

	bool Initialise(BackBuffer& backBuffer);

	void SpawnBigStars(int count, BackBuffer& backBuffer);
	void SpawnSmallStars(int count, BackBuffer& backBuffer);
	void SpawnStars(int count, const char* path, float speed, BackBuffer& backBuffer);
	void SpawnExplosionParticles(int count, const char* path, float x, float y, BackBuffer& backBuffer);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void ProcessStars(float deltaTime);
	void ProcessExplosions(float deltaTime);

	void DrawStars(BackBuffer& backBuffer);
	void DrawExplosions(BackBuffer& backBuffer);


protected:

private:

	// Member Fields:
public:

protected:

private:
	std::vector<StarParticle*> m_pStars;
	std::vector<ExplosionParticle*> m_pExplosions;

};

#endif // !__PARTICLE_EMITTER_H__
