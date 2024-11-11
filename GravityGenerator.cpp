#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(const Vector& gravity) : gravity(gravity) {}

void GravityGenerator::updateForce(CorpsRigide* rigidBody, float deltaTime)
{
    if (!rigidBody->hasInfiniteMass())
    {
        rigidBody->applyForce(gravity * rigidBody->getMass());
    }
}