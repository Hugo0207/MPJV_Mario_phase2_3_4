#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class GravityGenerator : public ForceGenerator
{
public:
	Vector gravity;

public:
	// Constructors
	GravityGenerator();
	GravityGenerator(float gravityMagnitude);

	// Add gravity to the selected particle resulting force
	virtual void updateForce(Particle* particle, float duration);


};

