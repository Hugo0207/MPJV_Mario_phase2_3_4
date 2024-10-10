#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vector.h"

class Particle {
protected:
    float inverseMass;
    float radius;

public:
    Vector position;
    Vector velocity; 
    ofColor color;
    Vector accumulatedForce;
    Vector normalVector(Particle* p) const;
    vector<Vector> trajectory;
	



public:
    Particle(Vector initPosition, Vector initVelocity, float inverseMass, ofColor color, float radius);
    ~Particle();

    void integrate(float deltaTime);
    void applyForce(const Vector& force);

    void draw();
	float getInverseMass() const;

    float getMass() const { return (inverseMass > 0.0f) ? 1.0f / inverseMass : 0.0f; }
    void setMass(float mass) { inverseMass = (mass > 0.0f) ? 1.0f / mass : 0.0f; }

    float distance(Particle* p);

    float get_radius() {
		return this->radius;
	}
};

#endif // PARTICLE_H
