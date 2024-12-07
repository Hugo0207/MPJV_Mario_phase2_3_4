#pragma once
#include "Vector.h"
#include "Quaternion.h"
#include "Matrice.h"
#include "Sphere.h"
#include "Plane.h"

class CorpsRigide
{
private:
    // Propri�t�s de masse
    float mass;
    float inverseMass;

    // Propri�t�s de mouvement lin�aire
    Vector position;
    Vector linearVelocity;
    Vector linearAcceleration;
    float dampingLinear;

    // Propri�t�s de mouvement angulaire
    Quaternion orientation;
    Vector angularVelocity;
    Vector angularAcceleration;
    float dampingAngular;

    // Tenseurs d'inertie
    Matrice<3> inertiaTensorLocal;
    Matrice<3> inverseInertiaTensorLocal;
    Matrice<3> inertiaTensorWorld;
    Matrice<3> inverseInertiaTensorWorld;

    // Accumulateurs de force et de torque
    Vector forceAccumulated;
    Vector torqueAccumulated;

    // Matrice de transformation
    Matrice<4> transformMatrix;

    // Point d'application de la force (pour la visualisation)
    Vector forceApplicationPoint;
    // Direction de la force (pour la visualisation)
    Vector forceDirection;
    // Position historique (pour la visualisation)
    std::vector<Vector> positionsHistory;

protected:
    Sphere* boundingSphere;

public:
    // Constructeur par d�faut
    CorpsRigide();
    virtual ~CorpsRigide() = default;

    virtual void createBoundingSphere();
    Sphere* getBoundingSphere() const;

    // Gestion de la masse
    void setMass(float mass);
    float getMass() const;
    bool hasInfiniteMass() const;

    // Gestion du tenseur d'inertie
    void setInertiaTensor(const Matrice<3> inertiaTensor);
    Matrice<3> getInertiaTensor() const;

    // Acc�s aux propri�t�s de position et d'orientation
    void setPosition(const Vector& position);
    Vector getPosition() const;

    void setOrientation(const Quaternion& orientation);
    Quaternion getOrientation() const;

    // Acc�s aux vitesses
    void setLinearVelocity(const Vector& velocity);
    Vector getLinearVelocity() const;

    void setAngularVelocity(const Vector& angularVelocity);
    Vector getAngularVelocity() const;

    // M�thodes pour appliquer des forces et des torques
    void applyForce(const Vector& force);
    void applyForceAtPoint(const Vector& force, const Vector& point);

    // Int�gration du mouvement
    void integrate(float deltaTime);

    // Gestion des accumulateurs
    void clearAccumulators();

    // Autres m�thodes utiles
    virtual void calculateDerivedData();
    Matrice<4> getTransformMatrix() const;

    void setForceApplicationPoint(const Vector& point);
    Vector getForceApplicationPoint() const;

    void setForceDirection(const Vector& direction);
    Vector getForceDirection() const;

    void addPositionHistory(const Vector& position);
    std::vector<Vector> getPositionsHistory() const;

    Vector getNormalVector(const CorpsRigide* otherCorpsRigide);
};
