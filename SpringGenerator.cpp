#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(Particle* otherParticle, float k, float restLength) : other(otherParticle), springConstant(k), restLength(restLength) {
}

void SpringGenerator::updateForce(Particle* particle, float duration) {

    if (!particle || !other) {
        return;  // Ne rien faire si l'un des pointeurs est invalide
    }

    // Calculer la distance entre les particles
    Vector displacement = particle->position - other->position;
    float length = displacement.norm();

    // Calculer la force de Hooke, magnitude F = -k * deltaX o� deltaX le d�placement par rapport � la longueur d'�quilibre du ressort
    float forceMagnitude = springConstant * (restLength - length);
    Vector springForce = displacement.normalize() * forceMagnitude; // Force mise sous forme de vecteur, normalize est un vecteur unitaire direction sans magnitude

    // Appliquer la force sur les deux particles
    particle->applyForce(springForce);
    other->applyForce(springForce * -1);  // Force �gale et oppos�e
}

