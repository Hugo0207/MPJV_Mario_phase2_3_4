#include "Vector.h"
#include <cmath>

// Constructors
Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(float initX, float initY) : x(initX), y(initY), z(0) {}

Vector::Vector(float initX, float initY, float initZ) : x(initX), y(initY), z(initZ) {}

// Norm calculations
float Vector::norm() const {
    return sqrt(x * x + y * y + z * z);
}

float Vector::squaredNorm() const {
    return x * x + y * y + z * z;
}

// Normalization
Vector Vector::normalize() const {
    float currentNorm = norm();
    return (currentNorm == 0) ? Vector(0, 0, 0) : Vector(x / currentNorm, y / currentNorm, z / currentNorm);
}

// Scalar multiplication
void Vector::scalarMul(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

// Vector operations
Vector Vector::add(const Vector& vectorToAdd) const {
    return Vector(x + vectorToAdd.x, y + vectorToAdd.y, z + vectorToAdd.z);
}

Vector Vector::sub(const Vector& vectorToSub) const {
    return Vector(x - vectorToSub.x, y - vectorToSub.y, z - vectorToSub.z);
}

Vector Vector::mul(const Vector& vectorToMul) const {
    return Vector(x * vectorToMul.x, y * vectorToMul.y, z * vectorToMul.z);
}

// Dot and cross products
float Vector::dotProduct(const Vector& vectorToUse) const {
    return x * vectorToUse.x + y * vectorToUse.y + z * vectorToUse.z;
}

Vector Vector::crossProduct(const Vector& vectorToUse) const {
    return Vector(
        y * vectorToUse.z - z * vectorToUse.y,
        z * vectorToUse.x - x * vectorToUse.z,
        x * vectorToUse.y - y * vectorToUse.x
    );
}

// Update method
void Vector::update(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
}

// Operator overloading
Vector Vector::operator+(const Vector& vec) const {
    return Vector(x + vec.x, y + vec.y, z + vec.z);
}

Vector Vector::operator-(const Vector& vec) const {
    return Vector(x - vec.x, y - vec.y, z - vec.z);
}

Vector Vector::operator*(float scalar) const {
    return Vector(x * scalar, y * scalar, z * scalar);
}

Vector Vector::operator/(float scalar) const {
    if (scalar == 0) throw std::invalid_argument("Division by zero");
    return Vector(x / scalar, y / scalar, z / scalar);
}

Vector& Vector::operator+=(const Vector& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector& Vector::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector& Vector::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vector::operator==(const Vector& vec) const {
    return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector::operator!=(const Vector& vec) const {
    return !(*this == vec);
}


