#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class SpringGenerator : public ForceGenerator{
public:
    Particle* particule;
    Particle* other;  // La deuxième particule
    float springConstant; // Constante de ressort
    float restLength;  // Longueur à l'équilibre du ressort

public:
    SpringGenerator(Particle* particule, Particle* otherParticle, float k, float restLength);
    virtual void updateForce(Particle* particle, float duration);
};

