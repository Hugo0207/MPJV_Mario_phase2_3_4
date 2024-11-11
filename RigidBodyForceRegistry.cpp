#include "RigidBodyForceRegistry.h"

// Constructeur par défaut
RigidBodyForceRegistry::RigidBodyForceRegistry()
{
    // Initialement, la liste des enregistrements est vide
}

// Ajoute un enregistrement au registre
void RigidBodyForceRegistry::add(CorpsRigide* rigidBody, RigidBodyForceGenerator* forceGenerator)
{
    RigidBodyForceRegistration registration;
    registration.rigidBody = rigidBody;
    registration.forceGenerator = forceGenerator;
    registrations.push_back(registration);
}

// Supprime un enregistrement du registre
void RigidBodyForceRegistry::remove(CorpsRigide* rigidBody, RigidBodyForceGenerator* forceGenerator)
{
    for (auto it = registrations.begin(); it != registrations.end(); ++it)
    {
        if (it->rigidBody == rigidBody && it->forceGenerator == forceGenerator)
        {
            registrations.erase(it);
            break;
        }
    }
}

// Efface tous les enregistrements
void RigidBodyForceRegistry::clear()
{
    registrations.clear();
}

// Met à jour toutes les forces dans le registre
void RigidBodyForceRegistry::updateForces(float deltaTime)
{
    for (auto& registration : registrations)
    {
        registration.forceGenerator->updateForce(registration.rigidBody, deltaTime);
    }
}
