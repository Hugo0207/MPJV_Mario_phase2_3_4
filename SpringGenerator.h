#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class SpringGenerator : public ForceGenerator {
public:
    Particle* other;  // La deuxi�me particule
    float springConstant; // Constante de ressort
    float restLength;  // Longueur � l'�quilibre du ressort

public:
    SpringGenerator();
    SpringGenerator(Particle* otherParticle, float k, float restLength);
    void updateForce(Particle* particle, float duration) override;

};

