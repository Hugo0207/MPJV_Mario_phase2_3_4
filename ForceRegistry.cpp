#include "ForceRegistry.h"

// Default constructor
ForceRegistry::ForceRegistry() {}

// Add a force to the registry
void ForceRegistry::add(Particle* particle, ForceGenerator* forceGenerator) {
	ForceRegistration registration = { particle, forceGenerator };
	registry.push_back(registration);
}

// Remove a force from the registry
void ForceRegistry::remove(Particle* particleToRemove, ForceGenerator* forceGeneratorToRemove) {
	int position = 0;
	for (auto& registration : registry) {
		if (registration.particle == particleToRemove && registration.forceGenerator == forceGeneratorToRemove) {
			registry.erase(registry.begin() + position);
		}
		position++;
	}
}

// Clear registry
void ForceRegistry::clear() {
	registry.clear();
}

// Update forces of every particle in the registry
void ForceRegistry::updateForces(float duration) {
	for (auto& registration : registry) {
		registration.forceGenerator->getName();
		registration.forceGenerator->updateForce(registration.particle, duration);
	}
}