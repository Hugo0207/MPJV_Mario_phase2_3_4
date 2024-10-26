#include <iostream>
#include <cmath>
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector.h"

class TestMatriceEtQuaternion {
public:
    static void testMatrix3Rotation() {
        Matrix3 mat;
        Vector axis(1.0f, 0.0f, 0.0f);
        float angle = PI / 2; 
        mat.setRotation(angle, axis);

        Vector vec(0.0f, 1.0f, 0.0f); 
        Vector result = mat * vec;

        std::cout << "Test Matrix3 Rotation: ";
        if (std::abs(result.x - 0.0f) < 1e-4 && std::abs(result.y - 0.0f) < 1e-4 && std::abs(result.z - 1.0f) < 1e-4) {
            std::cout << "Success\n";
        }
        else {
            std::cout << "Fail\n";
        }
    }

    static void testMatrix4Transform() {
        Matrix4 mat4;
        Matrix3 rotation;
        rotation.setRotation(PI / 2, Vector(0.0f, 1.0f, 0.0f)); 

        Vector translation(1.0f, 0.0f, 0.0f);
        mat4.setTransform(rotation, translation);

        Vector vec(0.0f, 0.0f, 1.0f); 
        Vector result = mat4 * vec;

        std::cout << "Test Matrix4 Transform: ";
        if (std::abs(result.x - 1.0f) < 1e-4 && std::abs(result.y - 0.0f) < 1e-4 && std::abs(result.z - 0.0f) < 1e-4) {
            std::cout << "Success\n";
        }
        else {
            std::cout << "Fail\n";
        }
    }

    static void testQuaternionNormalizationAndMultiplication() {
        Quaternion q1, q2;
        q1.fromAxisAngle(Vector(0.0f, 1.0f, 0.0f), PI / 2); 
        q2.fromAxisAngle(Vector(1.0f, 0.0f, 0.0f), PI / 2); 

        Quaternion result = q1 * q2; 

        result.normalize();
        std::cout << "Test Quaternion Normalization and Multiplication: ";
        if (std::abs(result.w - 0.5f) < 1e-4 && std::abs(result.x - 0.5f) < 1e-4 &&
            std::abs(result.y - 0.5f) < 1e-4 && std::abs(result.z - 0.5f) < 1e-4) {
            std::cout << "Success\n";
        }
        else {
            std::cout << "Fail\n";
        }
    }

    static void testQuaternionToMatrix3() {
        Quaternion q;
        q.fromAxisAngle(Vector(0.0f, 1.0f, 0.0f), PI / 2); 
        Matrix3 mat = q.toMatrix3();

        Vector vec(1.0f, 0.0f, 0.0f); 
        Vector result = mat * vec;

        std::cout << "Test Quaternion to Matrix3: ";
        if (std::abs(result.x - 0.0f) < 1e-4 && std::abs(result.y - 0.0f) < 1e-4 && std::abs(result.z - 1.0f) < 1e-4) {
            std::cout << "Success\n";
        }
        else {
            std::cout << "Fail\n";
        }
    }

    static void runTests() {
        testMatrix3Rotation();
        testMatrix4Transform();
        testQuaternionNormalizationAndMultiplication();
        testQuaternionToMatrix3();
    }
};

int main() {
    TestMatriceEtQuaternion::runTests();
    return 0;
}
