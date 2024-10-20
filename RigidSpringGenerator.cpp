#include "RigidSpringGenerator.h"

RigidSpringGenerator::RigidSpringGenerator(Particle* other, float restLength)
    : otherParticle(other), restLength(restLength) {}

void RigidSpringGenerator::updateForce(Particle* particle, float duration)
{
    Vector force = particle->getPosition() - otherParticle->getPosition();
    float currentLength = force.norm();

    // Si la distance dépasse la longueur au repos, appliquer une correction
    if (fabs(currentLength - restLength) > 0.001f) {
        float correction = (currentLength - restLength) / 2.0f;
        Vector correctionVector = force;
        correctionVector.normalize();
        correctionVector *= correction;

        particle->setPosition(particle->getPosition() - correctionVector);
        otherParticle->setPosition(otherParticle->getPosition() + correctionVector);
    }
}
