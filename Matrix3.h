#include <cmath>
#include "Vector.h"

class Matrix3 {
public:
    float m[3][3] = { {0.0f} };

    Matrix3() {
        m[0][0] = m[1][1] = m[2][2] = 1.0f;
    }

    Vector operator*(const Vector& v) const {
        return Vector(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
        );
    }

    Matrix3 operator*(const Matrix3& other) const {
        Matrix3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result.m[i][j] = m[i][0] * other.m[0][j] +
                    m[i][1] * other.m[1][j] +
                    m[i][2] * other.m[2][j];
            }
        }
        return result;
    }

    void setRotation(float angle, const Vector& axis) {
        float cosA = cos(angle);
        float sinA = sin(angle);
        float oneMinusCosA = 1.0f - cosA;

        m[0][0] = cosA + axis.x * axis.x * oneMinusCosA;
        m[0][1] = axis.x * axis.y * oneMinusCosA - axis.z * sinA;
        m[0][2] = axis.x * axis.z * oneMinusCosA + axis.y * sinA;
        m[1][0] = axis.y * axis.x * oneMinusCosA + axis.z * sinA;
        m[1][1] = cosA + axis.y * axis.y * oneMinusCosA;
        m[1][2] = axis.y * axis.z * oneMinusCosA - axis.x * sinA;
        m[2][0] = axis.z * axis.x * oneMinusCosA - axis.y * sinA;
        m[2][1] = axis.z * axis.y * oneMinusCosA + axis.x * sinA;
        m[2][2] = cosA + axis.z * axis.z * oneMinusCosA;
    }
};
