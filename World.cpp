#include "World.h"
#include "Boite.h"
#include <iostream>

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

void World::detectCollisions()
{
    for (auto* rigidBody : rigidBodies)
    {
        // Vérifier si le corps rigide est une boîte
        Boite* box = dynamic_cast<Boite*>(rigidBody);
        if (box)
        {
            // Récupérer les sommets transformés de la boîte
            auto vertices = box->getTransformedVertices();
            for (const auto& vertex : vertices)
            {
                // Calculer la distance par rapport au plan (y = 0)
                float t = vertex.y; // Normale du plan est (0, 1, 0) et Q = (0, 0, 0)

                if (t < 0)
                {
                    // Collision détectée avec le plan
                    std::cout << "Collision détectée au sommet: ("
                        << vertex.x << ", " << vertex.y << ", " << vertex.z << ")";

                        // Réagir à la collision (par ex. annuler la vitesse verticale)
                        Vector velocity = box->getLinearVelocity();
                    velocity.y = 0;
                    box->setLinearVelocity(velocity);

                    // Ajouter une légère correction pour sortir la boîte du plan
                    Vector position = box->getPosition();
                    position.y += 0.01f; // Correction
                    box->setPosition(position);
                }
            }
        }
    }
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

void World::updateOctree() {
    BoundingBox worldBounds(Vector(0, 0, 0), Vector(1000, 1000, 1000)); 
    delete octree; 
    octree = new OctreeNode(worldBounds); 

    for (auto* rigidBody : rigidBodies) {
        if (auto* box = dynamic_cast<Boite*>(rigidBody)) {
            auto vertices = box->getTransformedVertices();
            Vector min = vertices[0];
            Vector max = vertices[0];
            for (const auto& vertex : vertices) {
                min = Vector::min(min, vertex);
                max = Vector::max(max, vertex);
            }
            BoundingBox boxBounds(min, max);
            Object* obj = new Object(box->getPosition(), (max - min).norm() / 2.0f);
            octree->Insert(obj);
        }
    }
}

