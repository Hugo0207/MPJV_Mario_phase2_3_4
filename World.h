#pragma once
#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityGenerator.h"
#include "Collision.h"

class World
{
public:
	// Constructors
	World();
	World(float gravityMagnitude, float restitutionCoeff);

	// World force registry
	ForceRegistry* forceRegistry;

	// World gravity generator
	GravityGenerator* gravityGenerator;

	// World collision system
	Collision* collisionSystem;

	// Currently active particles
	std::vector<Particle*> particles;

	// Apply world forces on a given duration
	void applyWorldForces(float duration);
};

