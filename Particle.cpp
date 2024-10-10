#include "Particle.h"
#include <ofMain.h>

// Constructeur
Particle::Particle(Vector initPosition, Vector initVelocity, float initInverseMass)
	: position(initPosition), velocity(initVelocity), inverseMass(initInverseMass), accumulatedForce(0, 0, 0) {}

// Destructeur
Particle::~Particle() {}


// Intégration de la particule en fonction du temps écoulé depuis la dernière frame avec la méthode Verlet
void Particle::integrate(float deltaTime) {
    if (inverseMass <= 0.0f) return;

    // Calcul de l'accélération à partir de la force accumulée
    Vector acceleration = accumulatedForce * inverseMass;

    // Mise à jour de la position avec Verlet
    Vector newPosition = position + (velocity * deltaTime) + (acceleration * (0.5f * deltaTime * deltaTime));

    // Mise à jour de la vélocité avec Euler semi-implicite
    velocity = velocity + (acceleration * deltaTime);

    // Mise à jour de la position et ajout à la trajectoire
    position = newPosition;
    trajectory.push_back(position);

    // Réinitialisation de la force accumulée
    accumulatedForce = Vector(0, 0, 0);
}


// Application de la force à la particule
void Particle::applyForce(const Vector& force) {
    accumulatedForce += force;
    
}

void Particle::draw() {
    // Dessine la trajectoire
    ofSetColor(255, 255, 255); 
    for (size_t i = 1; i < trajectory.size(); ++i) {
        ofDrawLine(trajectory[i - 1].x, trajectory[i - 1].y, trajectory[i].x, trajectory[i].y);
    }

	// Dessine la particule
    ofSetColor(255, 0, 0); 
    ofDrawCircle(position.x, position.y, 5);
}

float Particle::getInverseMass() const {
    return inverseMass;
}

