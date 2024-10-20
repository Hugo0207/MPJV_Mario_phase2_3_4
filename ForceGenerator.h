#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	virtual void updateForce(Particle* particle, float duration);
	virtual void getName() {
		cout << "force" << endl;
	};
};

