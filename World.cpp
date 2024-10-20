#include "World.h"

World::World() : forceRegistry(ForceRegistry()), gravityGenerator(GravityGenerator(9.81)), frictionGenerator(FrictionGenerator(0.5)), collisionSystem(Collision(1, gravityGenerator.gravity))
{


	int centerX = ofGetWidth() / 2;
	int centerY = ofGetHeight() / 2;

	SpawnParticle(Vector(0, centerY + 50), Vector(0, 0), ofColor(255, 0, 0));
	//SpawnParticle(Vector(0, centerY), Vector(30, -50), ofColor(0, 255, 0));


	player = new Player(Vector(0, centerY), Vector(0, 0), 1, ofColor(0, 255, 0), 20);
	particles.push_back(player);
}

World::World(float gravityMagnitude, float restitutionCoeff) :
	forceRegistry(ForceRegistry()),
	gravityGenerator(GravityGenerator(gravityMagnitude)),
	frictionGenerator(FrictionGenerator(0.5)),
	/*springGenerator(),
	rigidSpringGenerator(), 
	elasticSpringGenerator(), 
	springHooke1Generator(),*/
	collisionSystem(Collision(restitutionCoeff, gravityGenerator.gravity))
{
}

void World::applyWorldForces(float duration)
{
	// Apply gravity to every world particle
	for (auto& particle : particles) {
		//forceRegistry.add(particle, &gravityGenerator);
	}

	for (auto& particle : particles) {
		if (particle != player) {

			ForceGenerator * springGenerator = new SpringGenerator(player, 1, 25);
			ForceGenerator * springGeneratorPlayer = new SpringGenerator(particle, 1, 25);

			//forceRegistry.add(particle, springGenerator);
			//forceRegistry.add(player, springGeneratorPlayer);
			
		}
	}
	
	// Apply every registry forces to their given particle
	forceRegistry.updateForces(duration);

	for (auto& particle : particles)
	{
		particle->integrate(duration);

	}

	collisionSystem.update(particles, duration);

	// Reset registry for next frame
	forceRegistry.clear();
}



//--------------------------------------------------------------
void World::SpawnParticle(Vector initPosition, Vector initVelocity, ofColor color) {
	Particle* newParticle = new Particle(
		initPosition,
		initVelocity,
		20,
		ofColor(color),
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
