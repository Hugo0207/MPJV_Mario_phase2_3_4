#include "World.h"

World::World() : forceRegistry(&ForceRegistry()), gravityGenerator(&GravityGenerator(9.81)), frictionGenerator(&FrictionGenerator(0.5)),
springGenerator(), rigidSpringGenerator(), elasticSpringGenerator(), springHooke1Generator(), collisionSystem(&Collision(1, &gravityGenerator->gravity)) {}

World::World(float gravityMagnitude, float restitutionCoeff) :
	forceRegistry(&ForceRegistry()),
	gravityGenerator(&GravityGenerator(gravityMagnitude)),
	frictionGenerator(&FrictionGenerator(0.5)),
	springGenerator(),
	rigidSpringGenerator(), 
	elasticSpringGenerator(), 
	springHooke1Generator(),
	collisionSystem(&Collision(restitutionCoeff, &gravityGenerator->gravity))
{}

void World::applyWorldForces(float duration)
{
	for (auto& particle : particles) {
		forceRegistry->add(particle, gravityGenerator);
		forceRegistry->add(particle, frictionGenerator);
		forceRegistry->add(particle, springGenerator);
		forceRegistry->add(particle, rigidSpringGenerator);
		forceRegistry->add(particle, elasticSpringGenerator);
		forceRegistry->add(particle, springHooke1Generator);
	}

	forceRegistry->updateForces(duration);
}
