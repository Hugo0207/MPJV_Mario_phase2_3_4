#include "QuaternionTest.h"
#include <iostream>

void QuaternionTest::runTests() {
    testConstructors();
    testGetters();
    testSetters();
    testInverse();
    testNegate();
    testMultiply();
    testApplyRotation();
    //testDifference();
    testDotProduct();
    testExponentiation();
    testConvertToMatrix();
    std::cout << "All tests passed!" << std::endl;
}

bool QuaternionTest::eq(float a, float b) {
    return std::abs(a - b) <= 1e-4f;
}

void QuaternionTest::testInverse() {
    Quaternion q1(180.0f, Vector(1, 1, 5));
    Quaternion q2 = q1.inverse();

    assert(eq(q2.w, q1.w));
    assert(q2.xyzVector == q1.xyzVector * (-1.0f));
}

void QuaternionTest::testNegate() {
    Quaternion q1(180.0f, Vector(1, 1, 5));
    Quaternion q2(-q1.w, -q1.xyzVector);

    assert(eq(q2.w, -q1.w));
    assert(q2.xyzVector == q1.xyzVector * (-1.0f));
}

void QuaternionTest::testMultiply() {
    Quaternion q1(1.0f, Vector(2, 3, 4));
    Quaternion q2(2.0f, Vector(3, 4, 5));
    Quaternion q3 = q1 * q2;

    assert(eq(q3.w, -36.0f));
    assert(q3.xyzVector == Vector(6.0f, 12.0f, 12.0f));
}

void QuaternionTest::testApplyRotation() {
    Vector targetVector(1, 0, 1);
    Quaternion q1(90.0f, Vector(0, 0, 1));
    Vector resVector = q1.applyRotation(targetVector);

    assert(resVector == Vector(0.0f, 1.0f, 1.0f));
}

//void QuaternionTest::testDifference() {
//    Quaternion q1(180.0f, Vector(1, 1, 1));
//    Quaternion qDiff = q1.difference(q1);
//
//    assert(eq(qDiff.w, 1.0f));
//    assert(qDiff.xyzVector == Vector(0.0f, 0.0f, 0.0f));
//}

void QuaternionTest::testDotProduct() {
    Quaternion q1(1.0f, Vector(2, 3, 4));
    Quaternion q2(2.0f, Vector(3, 4, 5));
    float dotProduct = q1.dotProduct(q2);

    assert(eq(dotProduct, 40.0f));
}

void QuaternionTest::testExponentiation() {
    Quaternion q1(10.0f, Vector(1, 0, 0));
    Quaternion q2 = q1.exponentiation(3.0f);

    assert(eq(q2.getRotationAngle(), 30.0f));
}

void QuaternionTest::testGetters() {
    Quaternion q1(180.0f, Vector(1, 0, 0));

    assert(eq(q1.getRotationAngle(), 180.0f));
    assert(q1.getRotationAxis() == Vector(1.0f, 0.0f, 0.0f));
}

void QuaternionTest::testSetters() {
    Quaternion q1(180.0f, Vector(3, 3, 3));
    q1.setRotationAngle(120.0f);
    q1.setRotationAxis(Vector(0, 0, 1));

    assert(eq(q1.getRotationAngle(), 120.0f));
    assert(q1.getRotationAxis() == Vector(0.0f, 0.0f, 1.0f));
}

void QuaternionTest::testConstructors() {
    Quaternion q1(180.0f, Vector(3, 3, 3));
    Quaternion q2(120.0f, Vector(3, 3, 3));

    assert(eq(q1.w, 0.0f));
    assert(eq(q2.w, 0.5f));

    Vector expectedXYZ(0.5f, 0.5f, 0.5f);
    Vector actualXYZ = q2.xyzVector;
    assert(actualXYZ == expectedXYZ);

    assert(eq(q1.norm(), 1.0f));
    assert(eq(q2.norm(), 1.0f));
}

void QuaternionTest::testConvertToMatrix() {
    Quaternion q1(1.0f, Vector(2, 3, 4));
    Matrice<3> m = q1.convertToMatrix();

    assert(eq(m.values[0][0], -49.0f));
    assert(eq(m.values[0][1], 20.0f));
    assert(eq(m.values[0][2], 20.0f));
    assert(eq(m.values[1][0], 4.0f));
    assert(eq(m.values[1][1], -39.0f));
    assert(eq(m.values[1][2], 28.0f));
    assert(eq(m.values[2][0], 22.0f));
    assert(eq(m.values[2][1], 20.0f));
    assert(eq(m.values[2][2], -25.0f));
}
