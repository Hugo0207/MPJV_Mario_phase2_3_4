#include "World.h"

World::World() : forceRegistry(ForceRegistry()), gravityGenerator(GravityGenerator(9.81)), collisionSystem(Collision(1, gravityGenerator.gravity)) {}

World::World(float gravityMagnitude, float restitutionCoeff) :
	forceRegistry(ForceRegistry()),
	gravityGenerator(GravityGenerator(gravityMagnitude)),
	collisionSystem(Collision(restitutionCoeff, gravityGenerator.gravity))
{}

void World::applyWorldForces(float duration)
{
	// Apply gravity to every world particle
	for (auto& particle : particles) {
		forceRegistry.add(particle, &gravityGenerator);
	}

	// Apply every registry forces to their given particle
	forceRegistry.updateForces(duration);

	for (auto& particle : particles)
	{
		particle->integrate(duration);

		// Stop les projectiles qui sont sortis de l'écran
		if (particle->position.y > ofGetHeight() * 1.3 || particle->position.x > ofGetWidth() * 1.3 || particle->position.x < 0) {
			particle->velocity = Vector(0, 0, 0);
		}
	}

	collisionSystem.update(particles, duration);

	// Reset registry for next frame
	forceRegistry.clear();
}
