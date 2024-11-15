#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <ofMain.h>

/**
 * @brief A class representing a 2D/3D vector and providing various vector operations.
 */
class Vector {

public:
    float x;
    float y;
    float z;

    // Constructors
    Vector(); // Default constructor for (0, 0, 0)
    Vector(float initX, float initY); // 2D vector
    Vector(float initX, float initY, float initZ); // 3D vector

    // Norm calculations
    float norm() const;
    float squaredNorm() const;

    // Normalization
    Vector normalize() const;

    // Scalar multiplication
    void scalarMul(float scalar);

    // Vector operations
    Vector add(const Vector& vectorToAdd) const;
    Vector sub(const Vector& vectorToSub) const;
    Vector mul(const Vector& vectorToMul) const;

    // Dot and cross products
    float dotProduct(const Vector& vectorToUse) const;
    Vector crossProduct(const Vector& vectorToUse) const;

    // Projection 
    Vector projectTo(const Vector& targetVector) const;

    // Update method
    void update(float newX, float newY, float newZ = 0.0f);

    // Operator overloading
    Vector operator+(const Vector& vec) const;
    Vector operator-(const Vector& vec) const;
    Vector operator*(float scalar) const;
    Vector operator/(float scalar) const;
    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(float scalar);
    Vector& operator/=(float scalar);
    Vector operator-() const;
    bool operator==(const Vector& vec) const;
    bool operator!=(const Vector& vec) const;


    // Conversion to glm types
    glm::vec2 toVec2() const { return glm::vec2(x, y); }
    glm::vec3 toVec3() const { return glm::vec3(x, y, z); }
};

#endif // VECTOR_H
