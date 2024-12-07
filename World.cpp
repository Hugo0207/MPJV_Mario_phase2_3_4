#include "World.h"
#include "Boite.h"
#include <iostream>

World::World(float deltaTime) : deltaTime(deltaTime), collisionSystem(Collision(1., Vector(0., -9.81, 0.))), octree(&OctreeNode()) {}


void World::addRigidBody(CorpsRigide* rigidBody)
{
    rigidBodies.push_back(rigidBody);
}

void World::removeRigidBody(CorpsRigide* rigidBody)
{
    rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), rigidBody), rigidBodies.end());
}

void World::addPlane(Plane* plane)
{
    planes.push_back(plane);
}

void World::removePlane(Plane* plane)
{
    planes.erase(std::remove(planes.begin(), planes.end(), plane), planes.end());
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
    updateOctree();
    collisionSystem.update(rigidBodies, planes, deltaTime);
}

const std::vector<CorpsRigide*>& World::getRigidBodies() const
{
    return rigidBodies;
}

const std::vector<Plane*>& World::getPlanes() const
{
    return planes;
}

void World::updateOctree() {
    BoundingBox worldBounds(Vector(-500, -500, -500), Vector(500, 500, 500));
    delete octree; 
    octree = new OctreeNode(worldBounds); 

    for (auto* rigidBody : rigidBodies) {
        Sphere* boundingSphere = rigidBody->getBoundingSphere();
        octree->Insert(boundingSphere);
    }
    //octree->Display();
}

