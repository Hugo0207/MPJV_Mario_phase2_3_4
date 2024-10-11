#pragma once

#include "Vector.h"
#include "Particle.h"

class Collision
{
private:
	float elasticityCoeff;

public:

	Collision(float elasticityCoeff);

		
	void update(std::vector<Particle*> Particles);

	bool detectionCollision(Particle* pA, Particle* pB);

	Vector impactPoint(Particle* pA, Particle* pB);

	float proportionalMove(Particle* pA, Particle* pB);

	void resolveDetection(Particle * pA, Particle * pB);


};