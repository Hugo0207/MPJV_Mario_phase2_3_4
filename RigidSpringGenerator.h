#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class RigidSpringGenerator : public ForceGenerator {
public:
    Particle* otherParticle;
    float restLength;

    RigidSpringGenerator();
    RigidSpringGenerator(Particle* other, float restLength);

    virtual void updateForce(Particle* particle, float duration);
};

