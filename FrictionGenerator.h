#pragma once

#include "ForceGenerator.h"
#include "Vector.h"

class FrictionGenerator : public ForceGenerator {
public:
	float frictionCoefficient;

public:
	FrictionGenerator();
	FrictionGenerator(float coefficient);

	virtual void updateForce(Particle* particle, float duration);
};

