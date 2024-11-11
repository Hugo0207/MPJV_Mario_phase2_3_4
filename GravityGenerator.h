#pragma once
#include "Vector.h"

#include "RigidBodyForceGenerator.h"

class GravityGenerator : public RigidBodyForceGenerator
{
private:
    Vector gravity;

public:
    GravityGenerator(const Vector& gravity);

    void updateForce(CorpsRigide* rigidBody, float deltaTime) override;
};

