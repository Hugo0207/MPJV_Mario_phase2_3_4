#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(Particle* particule, Particle* otherParticle, float k, float restLength) : particule(particule), other(otherParticle), springConstant(k), restLength(restLength) {}

void SpringGenerator::updateForce(Particle* particle, float duration) {
    if (!particule || !other) {
        return;  // Ne rien faire si l'un des pointeurs est invalide
    }

    // Calculer la distance entre les particules
    Vector displacement = particule->position - other->position;
    float length = displacement.norm();

    // Calculer la force de Hooke, magnitude F = -k * deltaX où deltaX le déplacement par rapport à la longueur d'équilibre du ressort
    float forceMagnitude = springConstant * (restLength - length);
    Vector springForce = displacement.normalize() * -forceMagnitude; // Force mise sous forme de vecteur, normalize est un vecteur unitaire direction sans magnitude

    // Appliquer la force sur les deux particules
    particule->applyForce(springForce);
    other->applyForce(springForce * -1);  // Force égale et opposée
}
