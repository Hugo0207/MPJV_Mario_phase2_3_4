#include <cmath>
#include "Vector.h"
#include "Matrix3.h"

class Matrix4 {
public:
    float m[4][4] = { {0.0f} };

    Matrix4() {
        for (int i = 0; i < 4; ++i) {
            m[i][i] = 1.0f;
        }
    }

    Vector operator*(const Vector& v) const {
        return Vector(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]
        );
    }

    void setTransform(const Matrix3& rotation, const Vector& translation) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] = rotation.m[i][j];
            }
        }
        m[0][3] = translation.x;
        m[1][3] = translation.y;
        m[2][3] = translation.z;
        m[3][0] = m[3][1] = m[3][2] = 0.0f;
        m[3][3] = 1.0f;
    }
};
