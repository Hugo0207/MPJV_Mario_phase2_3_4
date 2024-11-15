#include "World.h"

World::World(float deltaTime) : deltaTime(deltaTime) {}


void World::addRigidBody(CorpsRigide* rigidBody)
{
    rigidBodies.push_back(rigidBody);
}

void World::removeRigidBody(CorpsRigide* rigidBody)
{
    rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), rigidBody), rigidBodies.end());
}


void World::addForceGenerator(CorpsRigide* rigidBody, RigidBodyForceGenerator* fg)
{
    forceRegistry.add(rigidBody, fg);
}

void World::removeForceGenerator(CorpsRigide* rigidBody, RigidBodyForceGenerator* fg)
{
    forceRegistry.remove(rigidBody, fg);
}


void World::update()
{
    // Mise � jour des forces
    forceRegistry.updateForces(deltaTime);

    // Int�gration du mouvement de chaque corps rigide
    for (auto rigidBody : rigidBodies)
    {
        rigidBody->integrate(deltaTime);
    }

    // Gestion des collisions � impl�menter ult�rieurement
}

const std::vector<CorpsRigide*>& World::getRigidBodies() const
{
    return rigidBodies;
}

