#pragma once
#include <vector>
#include "CorpsRigide.h"
#include "RigidBodyForceGenerator.h"

class RigidBodyForceRegistry
{
protected:
    // Structure pour enregistrer les associations entre corps rigides et g�n�rateurs de force
    struct RigidBodyForceRegistration
    {
        CorpsRigide* rigidBody;
        RigidBodyForceGenerator* forceGenerator;
    };

    // Liste des enregistrements
    std::vector<RigidBodyForceRegistration> registrations;

public:
    // Constructeur par d�faut
    RigidBodyForceRegistry();

    // M�thodes pour ajouter et supprimer des enregistrements
    void add(CorpsRigide* rigidBody, RigidBodyForceGenerator* forceGenerator);
    void remove(CorpsRigide* rigidBody, RigidBodyForceGenerator* forceGenerator);
    void clear();

    // Mise � jour de toutes les forces dans le registre
    void updateForces(float deltaTime);
};
