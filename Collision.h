#pragma once

#include "Vector.h"
#include "Particle.h"

class Collision
{
private:
	float restitutionCoeff;
	Vector* gravity;

public:

	Collision(float restitutionCoeff, Vector* gravity);

		
	void update(std::vector<Particle*> Particles, float deltaTime);

	bool detect(Particle* pA, Particle* pB);

	Vector impactPoint(Particle* pA, Particle* pB);

	float proportionalDetach(Particle* pA, Particle* pB);

	void resolve(Particle * pA, Particle * pB);


};