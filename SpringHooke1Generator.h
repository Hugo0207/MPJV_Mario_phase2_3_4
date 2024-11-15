#pragma once

#include "ForceGenerator.h"
#include "Vector.h"

class SpringHooke1Generator : public ForceGenerator {
public:
    // Pour une particule reli�e � un point fixe
    Vector anchor; // Coordonn�es du point fixe
    float k; // Constante du ressort
    float restLength; // Longueur au repos

    SpringHooke1Generator();
    SpringHooke1Generator(Vector anchor, float springConstant, float restLength);

    // Pour les deux types de ressorts (point fixe et deux particules)
    virtual void updateForce(Particle* particle, float duration);
};

