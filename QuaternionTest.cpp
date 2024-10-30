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
    testDifference();
    testDotProduct();
    testExponentiation();
    std::cout << "All tests passed!" << std::endl;
}

bool QuaternionTest::eq(float a, float b)
{
    return abs(a - b) <= 1e-4;
}

void QuaternionTest::testInverse()
{
    Quaternion q1 = Quaternion(180, Vector(1, 1, 5));
    Quaternion q2 = *q1.inverse();

    assert(eq(q2.w, q1.w));
    assert(q2.xyzVector == q1.xyzVector * (-1));
}

void QuaternionTest::testNegate()
{
    Quaternion q1 = Quaternion(180, Vector(1, 1, 5));
    Quaternion q2 = *q1.inverse();

    assert(eq(q2.w, -q1.w));
    assert(q2.xyzVector == q1.xyzVector * (-1));
}

void QuaternionTest::testMultiply()
{
    Quaternion* q1 = Quaternion::createQuat(1, Vector(2,3,4));
    Quaternion* q2 = Quaternion::createQuat(2, Vector(3,4,5));
    Quaternion* q3 = q1->multiply(q2);

    assert(eq(q3->w, 2.f));
    assert(q3->xyzVector == Vector(-240.f,-480.f,-480.f));
}

void QuaternionTest::testApplyRotation()
{
    Vector* targetVector = new Vector(1,0,1);
    Quaternion q1 = Quaternion(90, Vector(0,0,1));
    Vector resVector = q1.applyRotation(targetVector);

    assert(resVector == Vector(0.f, 1.f, 1.f));
}

void QuaternionTest::testDifference()
{
    Quaternion q1 = Quaternion(180, Vector(1, 1, 1));
    Quaternion* qDiff = q1.difference(&q1);

    assert(qDiff->xyzVector == Vector(0.f, 0.f, 0.f));
}

void QuaternionTest::testDotProduct()
{
    Quaternion* q1 = Quaternion::createQuat(1, Vector(2, 3, 4));
    Quaternion* q2 = Quaternion::createQuat(2, Vector(3, 4, 5));
    float dotProduct = q1->dotProduct(q2);

    assert(eq(dotProduct, 40.f));
}

void QuaternionTest::testExponentiation()
{
    Quaternion q1 = Quaternion(10, Vector(1, 0, 0));
    Quaternion* q2 = q1.exponentiation(3);

    assert(eq(q2->getRotationAngle(), 30.f));
}

void QuaternionTest::testGetters()
{
    Quaternion q1 = Quaternion(180, Vector(1, 0, 0));

    assert(eq(q1.getRotationAngle(), 180.f));
    assert(q1.getRotationAxis() == Vector(1.f, 0.f, 0.f));
}

void QuaternionTest::testSetters()
{
    Quaternion q1 = Quaternion(180, Vector(3, 3, 3));
    q1.setRotationAngle(120);
    q1.setRotationAxis(Vector(0, 0, 1));

    assert(eq(q1.getRotationAngle(), 120.f));
    assert(q1.getRotationAxis() == Vector(0.f, 0.f, 1.f));
}

void QuaternionTest::testConstructors()
{
    Quaternion q1 = Quaternion(180, Vector(3, 3, 3));
    Quaternion q2 = Quaternion(120, Vector(3, 3, 3));

    assert(eq(q1.w, 0.f));
    assert(eq(q2.w, 0.5f) && q2.xyzVector == Vector(0.5f, 0.5f, 0.5f));
}
