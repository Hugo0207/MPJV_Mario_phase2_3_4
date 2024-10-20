#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class ElasticSpringGenerator : public ForceGenerator{
public:
    Particle* otherParticle;
    float k;
    float restLength;

    ElasticSpringGenerator(Particle* other, float springConstant, float restLength);

    virtual void updateForce(Particle* particle, float duration);
};

