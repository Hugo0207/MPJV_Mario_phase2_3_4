#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class SpringGenerator : public ForceGenerator{
public:
    Particle* other;  // La deuxième particule
    float springConstant; // Constante de ressort
    float restLength;  // Longueur à l'équilibre du ressort

public:
    SpringGenerator();
    SpringGenerator(Particle* otherParticle, float k, float restLength);
    void updateForce(Particle* particle, float duration) override;

    void getName() override;
};

