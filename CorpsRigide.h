#pragma once
#include "Vector.h"

class CorpsRigide
{
public:
    Vector position;
    Vector vitesse;
    Vector acceleration;
    Vector forceAccumulateur; 
    Vector rotation; 
    Vector centreDeMasse;
    float masse;
    float momentInertie; 
    float angleRotation; 
    float amortissement;

    CorpsRigide(const Vector& pos, const Vector& vit, float m, float damp = 0.98f)
        : position(pos), vitesse(vit), masse(m), amortissement(damp), angleRotation(0.0f) {
        if (masse != 0.0f) {
            momentInertie = calculerMomentDInertie();
        }
        else {
            momentInertie = 0.0f;
        }
        forceAccumulateur = Vector(0.0f, 0.0f, 0.0f);
        rotation = Vector(0.0f, 0.0f, 0.0f);
    }

    void appliquerForce(const Vector& force, const Vector& pointApplication) {
        forceAccumulateur += force;
        rotation += (pointApplication - centreDeMasse).crossProduct(force); 
    }

    void integrer(float deltaTime) {
        if (masse <= 0.0f) return;

        acceleration = forceAccumulateur * (1.0f / masse);
        vitesse += acceleration * deltaTime;
        position += vitesse * deltaTime;

        if (momentInertie > 0.0f) {
            Vector accelRotation = rotation * (1.0f / momentInertie);
            angleRotation += accelRotation.norm() * deltaTime;
        }

        vitesse *= amortissement;
        rotation *= amortissement;

        clearAccumulators();
    }

    void clearAccumulators() {
        forceAccumulateur = Vector(0.0f, 0.0f, 0.0f);
        rotation = Vector(0.0f, 0.0f, 0.0f);
    }

private:
    float calculerMomentDInertie() {return masse * centreDeMasse.squaredNorm();}
};

