#pragma once
#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityGenerator.h"
#include "FrictionGenerator.h"
#include "SpringGenerator.h"
#include "ElasticSpringGenerator.h"
#include "RigidSpringGenerator.h"
#include "SpringHooke1Generator.h"
#include "Collision.h"
#include "Player.h"

class World
{


public:
	// Constructors
	World();
	World(float gravityMagnitude, float restitutionCoeff);

	// World force registry
	ForceRegistry forceRegistry;

	// World gravity generator
	GravityGenerator gravityGenerator;
  
	// World friction generator
	FrictionGenerator frictionGenerator;

	// World spring generator
	/*SpringGenerator springGenerator;

	// World 1 particle spring generator
	/*SpringHooke1Generator springHooke1Generator;

	// World Tige generator
	RigidSpringGenerator rigidSpringGenerator;

	// World Elastic generator
	ElasticSpringGenerator elasticSpringGenerator;*/

	// World collision system
	Collision collisionSystem;

	// Currently active particles
	std::vector<Particle*> particles;

	// Apply world forces on a given duration
	void applyWorldForces(float duration);

	void SpawnParticle(Vector initPosition, Vector initVelocity, ofColor color);

	void drawParticle();

	Player* player;

};


