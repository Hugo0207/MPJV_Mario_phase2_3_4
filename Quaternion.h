#include <cmath>
#include "Vector.h"
#include "Matrix4.h"

class Quaternion {
public:
    float w, x, y, z;

    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : w(w), x(x), y(y), z(z) {}

    void fromAxisAngle(const Vector& axis, float angle) {
        float halfAngle = angle * 0.5f;
        float sinHalfAngle = sin(halfAngle);
        w = cos(halfAngle);
        x = axis.x * sinHalfAngle;
        y = axis.y * sinHalfAngle;
        z = axis.z * sinHalfAngle;
    }

    void normalize() {
        float magnitude = sqrt(w * w + x * x + y * y + z * z);
        if (magnitude > 0.0f) {
            w /= magnitude;
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
    }

    Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }

    Matrix3 toMatrix3() const {
        Matrix3 mat;
        mat.m[0][0] = 1 - 2 * (y * y + z * z);
        mat.m[0][1] = 2 * (x * y - z * w);
        mat.m[0][2] = 2 * (x * z + y * w);
        mat.m[1][0] = 2 * (x * y + z * w);
        mat.m[1][1] = 1 - 2 * (x * x + z * z);
        mat.m[1][2] = 2 * (y * z - x * w);
        mat.m[2][0] = 2 * (x * z - y * w);
        mat.m[2][1] = 2 * (y * z + x * w);
        mat.m[2][2] = 1 - 2 * (x * x + y * y);
        return mat;
    }
};
