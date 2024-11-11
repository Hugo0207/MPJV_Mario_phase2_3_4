#pragma once
#include "Quaternion.h"
#include <cmath>
#include <stdexcept>
#include "Vector.h"
#include "Matrice.h"

// Définition de PI 
#ifndef PI
#define PI 3.14159265358979323846
#endif

class Quaternion
{
public:
    float w;
    Vector xyzVector;

    // Constructeurs
    Quaternion() : w(1.0f), xyzVector(1.0f,1.0f, 1.0f) {}
    Quaternion(float w, const Vector& xyzVector); // Constructeur avec composantes

    // Méthode statique pour créer un quaternion à partir d'un angle et d'un axe
    static Quaternion fromAxisAngle(float rotationAngle, const Vector& rotationAxis);

    // Méthodes
    float norm() const;
    Quaternion normalize() const;
    Quaternion conjugate() const;
    Quaternion inverse() const;

    Quaternion operator+(const Quaternion& other) const;
    Quaternion& operator+=(const Quaternion& other);

    Quaternion operator*(const Quaternion& other) const;
    Quaternion& operator*=(const Quaternion& other);

    Quaternion operator*(float scalar) const;
    Quaternion& operator*=(float scalar);
    Quaternion operator/(float scalar) const;
    Quaternion& operator/=(float scalar);
	Quaternion operator-() const;

    float dotProduct(const Quaternion& other) const;

    Vector applyRotation(const Vector& target) const;

    Quaternion exponentiation(float t) const;

    float getRotationAngle() const;
    Vector getRotationAxis() const;

    void setRotationAngle(float angle);
    void setRotationAxis(const Vector& axis);

    Matrice<3> convertToMatrix() const;

private:
    // Méthode privée pour éviter la redondance
    static Quaternion createQuat(float w, const Vector& xyzVector);
};