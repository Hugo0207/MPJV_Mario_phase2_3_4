#include "World.h"

World::World() : forceRegistry(ForceRegistry()), gravityGenerator(GravityGenerator(9.81)), frictionGenerator(FrictionGenerator(0.5)), collisionSystem(Collision(0.8, gravityGenerator.gravity))
{

	separate = false;
	int centerY = ofGetHeight();
	nbParticle = 10;

	for (int i = 0; i<nbParticle; i++)
	{
		SpawnParticle(Vector(150 + i, centerY), Vector(0, 0));
	}


}

World::World(float gravityMagnitude, float restitutionCoeff) :
	forceRegistry(ForceRegistry()),
	gravityGenerator(GravityGenerator(gravityMagnitude)),
	frictionGenerator(FrictionGenerator(0.5)),
	collisionSystem(Collision(restitutionCoeff, gravityGenerator.gravity))
{
}

void World::applyWorldForces(float duration)
{
	// Apply gravity to every world particle
	for (auto& particle : particles) {
		forceRegistry.add(particle, &gravityGenerator);

		if (particle->groundTouch)
		{
			forceRegistry.add(particle, &frictionGenerator);
		}
	}

	if (!separate)
	{
		for (int i = 0; i < particles.size(); i++ ) {
			for (int j =0; j<4; j++)
			{
				int indice = (i + j) % particles.size();

				ForceGenerator* springGenerator = new SpringGenerator(particles[i], 0.9, 1);
				ForceGenerator* springGeneratorPlayer = new SpringGenerator(particles[indice], 0.9, 1);

				forceRegistry.add(particles[indice], springGenerator);
				forceRegistry.add(particles[i], springGeneratorPlayer);
			}

		}
	}

	// Apply every registry forces to their given particle
	forceRegistry.updateForces(duration);

	

	for (auto& particle : particles)
	{
		particle->handleInput();
		particle->integrate(duration);

	}

	collisionSystem.update(particles, duration);

	// Reset registry for next frame
	forceRegistry.clear();
}



//--------------------------------------------------------------
void World::SpawnParticle(Vector initPosition, Vector initVelocity) {
	Particle* newParticle = new Particle(
		initPosition,
		initVelocity,
		20,
		20
	);
	particles.push_back(newParticle);
}


void World::drawParticle()
{
	for (auto& particle : particles) {
		particle->draw();
	}
}
