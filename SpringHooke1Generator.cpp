#include "SpringHooke1Generator.h"

SpringHooke1Generator::SpringHooke1Generator(Vector anchorPoint, float springConstant, float restLength)
    : anchor(anchorPoint), k(springConstant), restLength(restLength) {}

void SpringHooke1Generator::updateForce(Particle* particle, float duration)
{
    // Calcul de la force selon la loi de Hooke
    Vector force = particle->getPosition() - anchor;
    float magnitude = force.norm();
    magnitude = fabs(magnitude - restLength) * k;

    // Normaliser la force
    force.normalize();
    force *= -magnitude;

    particle->applyForce(force);
}
