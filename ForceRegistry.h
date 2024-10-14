#pragma once
#include "Particle.h"
#include "ForceGenerator.h"

class ForceRegistry
{

	// Structure coupling a particle and a force generator
	struct ParticleForceRegistration {
		Particle* particle;
		ForceGenerator* forceGenerator;
	};

	// Vector type storing every particle force registration
	typedef vector<ParticleForceRegistration> Registry;

protected:
	// Vector storing every particle force registration
	Registry registry;

public:

	// Default constructor
	ForceRegistry();

	// Add a force to the registry
	void add(Particle* particle, ForceGenerator* forceGenerator);

	// Remove a force from the registry
	void remove(Particle* particle, ForceGenerator* forceGenerator);

	// Clear registry
	void clear();

	// Update forces of every particle in the registry
	void updateForces(float duration);

};

