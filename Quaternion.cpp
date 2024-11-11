#include "Quaternion.h"



Quaternion::Quaternion(float w, const Vector& xyzVector)
    : w(w), xyzVector(xyzVector) {}

// Constructeur avec angle de rotation et axe
Quaternion Quaternion::fromAxisAngle(float rotationAngle, const Vector& rotationAxis)
{
    if (rotationAxis.norm() == 0.0f)
    {
        throw std::invalid_argument("L'axe de rotation ne peut pas être le vecteur nul.");
    }

    float halfRotationAngleRad = (rotationAngle * PI / 180.0f) / 2.0f;
    float w = cos(halfRotationAngleRad);
    Vector xyzVector = rotationAxis.normalize() * sin(halfRotationAngleRad);

    return Quaternion(w, xyzVector);
}




// Norme du quaternion
float Quaternion::norm() const
{
    return sqrt(w * w + xyzVector.x * xyzVector.x + xyzVector.y * xyzVector.y + xyzVector.z * xyzVector.z);
}

// Normalisation du quaternion
Quaternion Quaternion::normalize() const
{
    float n = norm();
    if (n == 0.0f)
    {
        throw std::runtime_error("Cannot normalize a quaternion with zero norm.");
    }
    return Quaternion(w / n, xyzVector / n);
}

// Conjugué du quaternion
Quaternion Quaternion::conjugate() const
{
    return Quaternion(w, xyzVector * (-1));
}

// Inverse du quaternion
Quaternion Quaternion::inverse() const
{
    float n = norm();
    if (n == 0.0f)
    {
        throw std::runtime_error("Cannot invert a quaternion with zero norm.");
    }
    return conjugate() / (n * n);
}

// Opérateur d'addition
Quaternion Quaternion::operator+(const Quaternion& other) const
{
    return Quaternion(w + other.w, xyzVector + other.xyzVector);
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
    w += other.w;
    xyzVector += other.xyzVector;
    return *this;
}

// Opérateur de multiplication par un quaternion
Quaternion Quaternion::operator*(const Quaternion& other) const
{
    float resW = w * other.w - xyzVector.dotProduct(other.xyzVector);
    Vector resXYZvector = xyzVector * other.w + other.xyzVector * w + xyzVector.crossProduct(other.xyzVector);

    return Quaternion(resW, resXYZvector);
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
    *this = *this * other;
    return *this;
}

// Opérateur de multiplication par un scalaire
Quaternion Quaternion::operator*(float scalar) const
{
    return Quaternion(w * scalar, xyzVector * scalar);
}

Quaternion& Quaternion::operator*=(float scalar)
{
    w *= scalar;
    xyzVector *= scalar;
    return *this;
}

Quaternion Quaternion::operator/(float scalar) const
{
    if (scalar == 0.0f)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return Quaternion(w / scalar, xyzVector / scalar);
}

Quaternion& Quaternion::operator/=(float scalar)
{
    if (scalar == 0.0f)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    w /= scalar;
    xyzVector /= scalar;
    return *this;
}

Quaternion Quaternion::operator-() const {
    return Quaternion(-w, -xyzVector);
}


// Produit scalaire
float Quaternion::dotProduct(const Quaternion& other) const
{
    return w * other.w + xyzVector.x * other.xyzVector.x + xyzVector.y * other.xyzVector.y + xyzVector.z * other.xyzVector.z;
}

// Application d'une rotation à un vecteur
Vector Quaternion::applyRotation(const Vector& target) const
{
    Vector u = xyzVector;
    float s = w;
    return u * (2.0f * u.dotProduct(target))
        + target * (s * s - u.dotProduct(u))
        + u.crossProduct(target) * (2.0f * s);
}

// Exponentiation du quaternion
Quaternion Quaternion::exponentiation(float t) const
{
    float halfTheta = acos(w);
    float sinHalfTheta = sin(halfTheta);
    if (fabs(sinHalfTheta) < 1e-6f)
    {
        // Retourne le quaternion courant pour éviter la division par zéro
        return *this;
    }
    return Quaternion(cos(t * halfTheta), xyzVector * (sin(t * halfTheta) / sinHalfTheta));
}

// Obtient l'angle de rotation (en degrés)
float Quaternion::getRotationAngle() const
{
    return (2.0f * acos(w)) * 180.0f / PI;
}

// Obtient l'axe de rotation
Vector Quaternion::getRotationAxis() const
{
    float sinHalfTheta = sqrt(1.0f - w * w);
    if (sinHalfTheta < 1e-6f)
    {
        // L'axe est indéfini si l'angle est proche de 0 ou 180 degrés
        return Vector(1.0f, 0.0f, 0.0f); // Retourne un axe arbitraire
    }
    return xyzVector / sinHalfTheta;
}

// Modifie l'angle de rotation (en degrés)
void Quaternion::setRotationAngle(float angle)
{
    float halfRotationAngleRad = (angle * PI / 180.0f) / 2.0f;
    w = cos(halfRotationAngleRad);
    xyzVector = getRotationAxis() * sin(halfRotationAngleRad);
    *this = this->normalize();
}

// Modifie l'axe de rotation
void Quaternion::setRotationAxis(const Vector& axis)
{
    if (axis.norm() == 0.0f)
    {
        throw std::invalid_argument("L'axe de rotation ne peut pas être le vecteur nul.");
    }

    float halfRotationAngleRad = acos(w);
    xyzVector = axis.normalize() * sin(halfRotationAngleRad);
    *this = this->normalize();
}

// Conversion en matrice 3x3
Matrice<3> Quaternion::convertToMatrix() const
{
    float x = xyzVector.x;
    float y = xyzVector.y;
    float z = xyzVector.z;
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    return Matrice<3>({
        1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz),        2.0f * (xz + wy),
        2.0f * (xy + wz),        1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx),
        2.0f * (xz - wy),        2.0f * (yz + wx),        1.0f - 2.0f * (xx + yy)
        });
}

// Méthode privée pour créer un quaternion
Quaternion Quaternion::createQuat(float w, const Vector& xyzVector)
{
    return Quaternion(w, xyzVector);
}