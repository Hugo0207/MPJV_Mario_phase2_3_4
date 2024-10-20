#include "FrictionGenerator.h"

FrictionGenerator::FrictionGenerator() : frictionCoefficient(0.0) {};
FrictionGenerator::FrictionGenerator(float coefficient) : frictionCoefficient(coefficient){}

void FrictionGenerator::updateForce(Particle* particle, float duration) {
    Vector velocity = particle->velocity;
    Vector frictionForce = velocity * -frictionCoefficient; // F = -µ*v où µ coeff de friction et important - car force de friction toujours opposée au mouvement
    particle->applyForce(frictionForce);
}