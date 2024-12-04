#pragma once
#include <vector>
#include "CorpsRigide.h"
#include "RigidBodyForceRegistry.h"
#include "OctreeNode.h"

class World
{
private:
    std::vector<CorpsRigide*> rigidBodies;
    RigidBodyForceRegistry forceRegistry;
    float deltaTime;

public:
    World(float deltaTime);

    // Gestion des corps rigides
    void addRigidBody(CorpsRigide* rigidBody);
    void removeRigidBody(CorpsRigide* rigidBody);

    // Gestion des forces
    void addForceGenerator(CorpsRigide* rigidBody, RigidBodyForceGenerator* fg);
    void removeForceGenerator(CorpsRigide* rigidBody, RigidBodyForceGenerator* fg);

    // Mise � jour de la simulation
    void update();
    void updateOctree();
    OctreeNode* octree;

    //Détection des collisions
    void detectCollisions();

    // Acc�s aux corps rigides
    const std::vector<CorpsRigide*>& getRigidBodies() const;

    // Accesseurs
    float getDeltaTime() const { return deltaTime; }
    void setDeltaTime(float deltaTime) { this->deltaTime = deltaTime; }
};
