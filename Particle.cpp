#include "Particle.h"
#include <ofMain.h>
#include <random>

// Constructeur
Particle::Particle(Vector initPosition, Vector initVelocity, float mass, float radius)
	: position(initPosition), velocity(initVelocity), inverseMass((mass > 0.0f) ? 1.0f / mass : 0.0f), radius(radius), accumulatedForce(0, 0, 0) {
    
    std::random_device rd;  // Source d'entropie
    std::mt19937 gen(rd()); // Générateur de nombres pseudo-aléatoires

    // Distribution uniforme entre 1 et 10
    std::uniform_int_distribution<> distr(1, 10);

    // Tirer un nombre au hasard
    int randomNumber = distr(gen);

    if (randomNumber <= 3) {
        player = true;
        color = ofColor(0, 255, 0);
    }
    else 
    {
        player = false;
        color = ofColor(255, 0, 0);
    }
}

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

    // R�initialisation de la force accumul�e
    accumulatedForce = Vector(0, 0, 0);
}


// Application de la force � la particule
void Particle::applyForce(const Vector& force) {
    accumulatedForce += force;

}

void Particle::draw() {
    // Dessine la particule
    ofSetColor(color);
    ofDrawCircle(position.x, position.y, radius);
}

float Particle::getInverseMass() const {
    return inverseMass;
}

// Distance entre le centre de deux particules
float Particle::distance(Particle* p)
{
    return (this->position - p->position).norm();
}



// Vecteur normal obtenu d'un couple de particules
Vector Particle::normalVector(Particle* p) const
{
    return (p->position - this->position) / (p->position - this->position).norm();
}

void Particle::handleInput() {
    if (player)
    {
        if (ofGetKeyPressed(OF_KEY_LEFT)) {
            setVelocity(getVelocity() + Vector(-1, 0, 0));
        }
        if (ofGetKeyPressed(OF_KEY_RIGHT)) {
            setVelocity(getVelocity() + Vector(1, 0, 0));
        }
        if (ofGetKeyPressed(OF_KEY_UP)) {
            setVelocity(getVelocity() + Vector(0, -2, 0));
        }
        if (ofGetKeyPressed(OF_KEY_DOWN)) {
            setVelocity(getVelocity() + Vector(0, 1, 0));
        }
    }
}

/*
    void Particle::handleInput() {
        if (player)
        {
            if (ofGetKeyPressed(OF_KEY_LEFT)) {
                accumulatedForce += Vector(-1, 0, 0);
            }
            if (ofGetKeyPressed(OF_KEY_RIGHT)) {
                accumulatedForce += Vector(1, 0, 0);
            }
            if (ofGetKeyPressed(OF_KEY_UP)) {
                accumulatedForce += Vector(0, -2, 0);
            }
            if (ofGetKeyPressed(OF_KEY_DOWN)) {
                accumulatedForce += Vector(0, 1, 0);
            }
        }
    }*/