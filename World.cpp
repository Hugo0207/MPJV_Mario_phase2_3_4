#include "World.h"

World::World() : forceRegistry(&ForceRegistry()), gravityGenerator(&GravityGenerator(9.81)), collisionSystem(&Collision(1, &gravityGenerator->gravity)) {}

World::World(float gravityMagnitude, float restitutionCoeff) :
	forceRegistry(&ForceRegistry()),
	gravityGenerator(&GravityGenerator(gravityMagnitude)),
	collisionSystem(&Collision(restitutionCoeff, &gravityGenerator->gravity))
{}

void World::applyWorldForces(float duration)
{
	for (auto& particle : particles) {
		forceRegistry->add(particle, gravityGenerator);
	}

	forceRegistry->updateForces(duration);
}
