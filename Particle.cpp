#include "Particle.h"
#include <ofMain.h>

// Constructeur
Particle::Particle(Vector initPosition, Vector initVelocity, float initInverseMass)
	: position(initPosition), velocity(initVelocity), inverseMass(initInverseMass), accumulatedForce(0, 0, 0) {}

// Destructeur
Particle::~Particle() {}


// Int�gration de la particule en fonction du temps �coul� depuis la derni�re frame avec la m�thode Verlet
void Particle::integrate(float deltaTime) {
    if (inverseMass <= 0.0f) return;

    // Calcul de l'acc�l�ration � partir de la force accumul�e
    Vector acceleration = accumulatedForce * inverseMass;

    // Mise � jour de la position avec Verlet
    Vector newPosition = position + (velocity * deltaTime) + (acceleration * (0.5f * deltaTime * deltaTime));

    // Mise � jour de la v�locit� avec Euler semi-implicite
    velocity = velocity + (acceleration * deltaTime);

    // Mise � jour de la position et ajout � la trajectoire
    position = newPosition;
    trajectory.push_back(position);

    // R�initialisation de la force accumul�e
    accumulatedForce = Vector(0, 0, 0);
}


// Application de la force � la particule
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

