#include "GravityGenerator.h"

// Constructors
GravityGenerator::GravityGenerator() : gravity(Vector(0, -9.81, 0)) {}

GravityGenerator::GravityGenerator(float gravityMagnitude) : gravity(Vector(0, gravityMagnitude, 0)) {}

// Add gravity to the selected particle resulting force
void GravityGenerator::updateForce(Particle* particle, float duration) {
	// Check if mass is valid
	int ParticleMass = particle->getMass();

	if (ParticleMass > 0.0f) {
		particle->applyForce(gravity * ParticleMass);
	}
}