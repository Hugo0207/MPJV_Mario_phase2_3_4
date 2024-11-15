#include "CorpsRigide.h"

CorpsRigide::CorpsRigide()
{
    // Masse infinie par d�faut (immobile)
    mass = 0.0f;
    inverseMass = 0.0f;

    // Mouvement lin�aire initialis� � z�ro
    position = Vector();
    linearVelocity = Vector();
    linearAcceleration = Vector();
    dampingLinear = 0.99f; // Valeur par d�faut pour le damping lin�aire

    // Mouvement angulaire initialis� � z�ro
    orientation = Quaternion(0.0f, Vector(0.0f, 0.0f, 1.0f));
    angularVelocity = Vector();
    angularAcceleration = Vector();
    dampingAngular = 0.99f; // Valeur par d�faut pour le damping angulaire

    // Tenseurs d'inertie initialis�s � l'identit�
    inertiaTensorLocal = Matrice<3>({
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
        });
    inverseInertiaTensorLocal = inertiaTensorLocal.inverse();

    // Accumulateurs initialis�s � z�ro
    forceAccumulated = Vector();
    torqueAccumulated = Vector();

    // Calcul des donn�es d�riv�es initiales
    calculateDerivedData();
}


// Gestion de la masse

void CorpsRigide::setMass(float mass)
{
    if (mass <= 0.0f)
    {
        throw std::invalid_argument("Mass must be greater than zero.");
    }
    this->mass = mass;
    inverseMass = 1.0f / mass;
}

float CorpsRigide::getMass() const
{
    return mass;
}

bool CorpsRigide::hasInfiniteMass() const
{
    return inverseMass == 0.0f;
}


// Gestion du Tenseur d'Inertie

void CorpsRigide::setInertiaTensor(const Matrice<3> inertiaTensor)
{
    inertiaTensorLocal = inertiaTensor;

    // V�rification que le tenseur d'inertie est valide
    float det = inertiaTensor.determinant();
    if (det == 0.0f)
    {
        throw std::invalid_argument("Inertia tensor must not be singular.");
    }

    inverseInertiaTensorLocal = inertiaTensor.inverse();
}

Matrice<3> CorpsRigide::getInertiaTensor() const
{
    return inertiaTensorLocal;
}


// Acc�s aux Propri�t�s de Position et d'Orientation

void CorpsRigide::setPosition(const Vector& position)
{
    this->position = position;
}

Vector CorpsRigide::getPosition() const
{
    return position;
}

void CorpsRigide::setOrientation(const Quaternion& orientation)
{
    this->orientation = orientation;
    this->orientation = this->orientation.normalize(); // Assure que le quaternion est normalis�
}

Quaternion CorpsRigide::getOrientation() const
{
    return orientation;
}

// Int�gration du Mouvement

void CorpsRigide::integrate(float deltaTime)
{
    if (hasInfiniteMass())
    {
        // Corps immobile
        return;
    }

    // Mise � jour de la position lin�aire
    position += linearVelocity * deltaTime;

    // Calcul de l'acc�l�ration r�sultante
    Vector resultingAcc = linearAcceleration;
    resultingAcc += forceAccumulated * inverseMass;

    // Mise � jour de la vitesse lin�aire
    linearVelocity += resultingAcc * deltaTime;

    // Application du damping lin�aire
    linearVelocity *= powf(dampingLinear, deltaTime);

    // Mise � jour de l'orientation
    Quaternion angularVelocityQuat(0.0f, angularVelocity);
    Quaternion deltaOrientation = angularVelocityQuat * orientation;
    orientation += deltaOrientation * (deltaTime * 0.5f);
    orientation = orientation.normalize(); // Assure que le quaternion reste normalis�

    // Calcul de l'acc�l�ration angulaire r�sultante
    Vector resultingAngularAcc = angularAcceleration;
    resultingAngularAcc += inverseInertiaTensorWorld * torqueAccumulated;

    // Mise � jour de la vitesse angulaire
    angularVelocity += resultingAngularAcc * deltaTime;

    // Application du damping angulaire
    angularVelocity *= powf(dampingAngular, deltaTime);

    // Calcul des donn�es d�riv�es pour la prochaine �tape
    calculateDerivedData();

    // Effacement des accumulateurs
    clearAccumulators();
}


// Calcul des Donn�es D�riv�es
void CorpsRigide::calculateDerivedData()
{
    // Calcul de la matrice de transformation � partir de la position et de l'orientation
    Matrice<3> rotationMatrix = orientation.convertToMatrix();

    // Mise � jour du tenseur d'inertie dans l'espace monde
    inertiaTensorWorld = rotationMatrix * inertiaTensorLocal * rotationMatrix.transpose();
    inverseInertiaTensorWorld = inertiaTensorWorld.inverse();

    // Construction de la matrice de transformation 4x4
    transformMatrix = Matrice<4>({
        rotationMatrix.values[0][0], rotationMatrix.values[0][1], rotationMatrix.values[0][2], position.x,
        rotationMatrix.values[1][0], rotationMatrix.values[1][1], rotationMatrix.values[1][2], position.y,
        rotationMatrix.values[2][0], rotationMatrix.values[2][1], rotationMatrix.values[2][2], position.z,
        0.0f,                   0.0f,                   0.0f,                   1.0f
        });
}

// Application des Forces et Torques


void CorpsRigide::applyForce(const Vector& force)
{
    forceAccumulated += force;
}

void CorpsRigide::applyForceAtPoint(const Vector& force, const Vector& point)
{
    // Calcul du vecteur du centre de masse au point d'application
    Vector pt = point - position;

    // Accumulation de la force et du torque
    forceAccumulated += force;
    torqueAccumulated += pt.crossProduct(force);
}


void CorpsRigide::clearAccumulators()
{
    forceAccumulated = Vector();
    torqueAccumulated = Vector();
}

// Acc�s aux vitesses lin�aires

void CorpsRigide::setLinearVelocity(const Vector& velocity)
{
    this->linearVelocity = velocity;
}

Vector CorpsRigide::getLinearVelocity() const
{
    return linearVelocity;
}

// Acc�s aux vitesses angulaires

void CorpsRigide::setAngularVelocity(const Vector& angularVelocity)
{
    this->angularVelocity = angularVelocity;
}

Vector CorpsRigide::getAngularVelocity() const
{
    return angularVelocity;
}

// Acc�s � la matrice de transformation

Matrice<4> CorpsRigide::getTransformMatrix() const
{
    return transformMatrix;
}


void CorpsRigide::setForceApplicationPoint(const Vector& point)
{
    forceApplicationPoint = point;
}

Vector CorpsRigide::getForceApplicationPoint() const
{
    return forceApplicationPoint;
}

void CorpsRigide::setForceDirection(const Vector& direction)
{
    forceDirection = direction;
}

Vector CorpsRigide::getForceDirection() const
{
    return forceDirection;
}

void CorpsRigide::addPositionHistory(const Vector& position)
{
    positionsHistory.push_back(position);

    // Limite la taille de positionsHistory � 500 positions
    if (positionsHistory.size() > 500)
    {
        positionsHistory.erase(positionsHistory.begin());
    }
}

std::vector<Vector> CorpsRigide::getPositionsHistory() const
{
    return positionsHistory;
}

