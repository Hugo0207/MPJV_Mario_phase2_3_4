#pragma once
#include <vector>
#include "CorpsRigide.h"
#include "RigidBodyForceRegistry.h"
#include "OctreeNode.h"
#include "Collision.h"
#include "Plane.h"

class World
{
private:
    std::vector<CorpsRigide*> rigidBodies;
    std::vector<Plane*> planes;
    RigidBodyForceRegistry forceRegistry;
    Collision collisionSystem;

    float deltaTime;

public:
    World(float deltaTime);

    // Gestion des corps rigides
    void addRigidBody(CorpsRigide* rigidBody);
    void removeRigidBody(CorpsRigide* rigidBody);

    // Gestion des plans
    void addPlane(Plane* plane);
    void removePlane(Plane* plane);

    // Gestion des forces
    void addForceGenerator(CorpsRigide* rigidBody, RigidBodyForceGenerator* fg);
    void removeForceGenerator(CorpsRigide* rigidBody, RigidBodyForceGenerator* fg);

    // Mise � jour de la simulation
    void update();
    void updateOctree();

    void drawOctree();

    OctreeNode* octree;

    // Acc�s aux corps rigides
    const std::vector<CorpsRigide*>& getRigidBodies() const;

    // Acc�s aux plans
    const std::vector<Plane*>& getPlanes() const;

    // Accesseurs
    float getDeltaTime() const { return deltaTime; }
    void setDeltaTime(float deltaTime) { this->deltaTime = deltaTime; }
};
