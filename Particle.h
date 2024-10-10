#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vector.h"

class Particle {
protected:
    float inverseMass;

public:
    Vector position;
    Vector velocity;  
    Vector accumulatedForce;
    vector<Vector> trajectory;
	



public:
    Particle(Vector initPosition, Vector initVelocity, float initInverseMass);
    ~Particle();

    void integrate(float deltaTime);
    void applyForce(const Vector& force);

    void draw();
	float getInverseMass() const;

    float getMass() const { return (inverseMass > 0.0f) ? 1.0f / inverseMass : 0.0f; }
    void setMass(float mass) { inverseMass = (mass > 0.0f) ? 1.0f / mass : 0.0f; }
};

#endif // PARTICLE_H
