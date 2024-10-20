#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(Particle* otherParticle, float k, float restLength) : other(otherParticle), springConstant(k), restLength(restLength) {
}

void SpringGenerator::updateForce(Particle* particle, float duration) {
    cout << "test" << endl;

    if (!particle || !other) {
        return;  // Ne rien faire si l'un des pointeurs est invalide
    }

    // Calculer la distance entre les particles
    Vector displacement = particle->position - other->position;
    float length = displacement.norm();

    // Calculer la force de Hooke, magnitude F = -k * deltaX où deltaX le déplacement par rapport à la longueur d'équilibre du ressort
    float forceMagnitude = springConstant * (restLength - length);
    Vector springForce = displacement.normalize() * -forceMagnitude; // Force mise sous forme de vecteur, normalize est un vecteur unitaire direction sans magnitude

    cout << "springForce" << endl;
    // Appliquer la force sur les deux particles
    particle->applyForce(springForce);
    other->applyForce(springForce * -1);  // Force égale et opposée
}

void SpringGenerator::getName() {
    cout << "SpringGenerator" << endl;
};
