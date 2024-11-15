#include "ElasticSpringGenerator.h"

ElasticSpringGenerator::ElasticSpringGenerator(Particle* other, float springConstant, float restLength)
    : otherParticle(other), k(springConstant), restLength(restLength) {}

void ElasticSpringGenerator::updateForce(Particle* particle, float duration)
{
    Vector force = particle->getPosition() - otherParticle->getPosition();
    float magnitude = force.norm();

    // Appliquer la force uniquement si le ressort est �tir� (magnitude > restLength)
    if (magnitude > restLength) {
        magnitude = (magnitude - restLength) * k;
        force.normalize();
        force *= -magnitude;
        particle->applyForce(force);
    }
}
