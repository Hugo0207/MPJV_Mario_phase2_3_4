#include "VectorTest.h"
#include <iostream>

void VectorTest::runTests() {
    testConstructors();
    testNorm();
    testNormalize();
    testScalarMul();
    testAdd();
    testSub();
    testDotProduct();
    testCrossProduct();
    testOperators();
    std::cout << "All tests passed!" << std::endl;
}

void VectorTest::testConstructors() {
    Vector v1;
    Vector v2(1, 2);
    Vector v3(1, 2, 3);

    assert(v1.x == 0 && v1.y == 0 && v1.z == 0);
    assert(v2.x == 1 && v2.y == 2 && v2.z == 0);
    assert(v3.x == 1 && v3.y == 2 && v3.z == 3);
}

void VectorTest::testNorm() {
    Vector v(1, 2, 2);
    assert(v.norm() == 3);
    assert(v.squaredNorm() == 9);
}

void VectorTest::testNormalize() {
    Vector v(1, 2, 2);
    Vector n = v.normalize();
    assert(n.x == 1.0 / 3.0 && n.y == 2.0 / 3.0 && n.z == 2.0 / 3.0);
}

void VectorTest::testScalarMul() {
    Vector v(1, 2, 3);
    v.scalarMul(2);
    assert(v.x == 2 && v.y == 4 && v.z == 6);
}

void VectorTest::testAdd() {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    Vector v3 = v1.add(v2);
    assert(v3.x == 5 && v3.y == 7 && v3.z == 9);
}

void VectorTest::testSub() {
    Vector v1(4, 5, 6);
    Vector v2(1, 2, 3);
    Vector v3 = v1.sub(v2);
    assert(v3.x == 3 && v3.y == 3 && v3.z == 3);
}

void VectorTest::testDotProduct() {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    assert(v1.dotProduct(v2) == 32);
}

void VectorTest::testCrossProduct() {
    Vector v1(1, 0, 0);
    Vector v2(0, 1, 0);
    Vector v3 = v1.crossProduct(v2);
    assert(v3.x == 0 && v3.y == 0 && v3.z == 1);
}

void VectorTest::testOperators() {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);

    Vector v3 = v1 + v2;
    assert(v3.x == 5 && v3.y == 7 && v3.z == 9);

    Vector v4 = v1 - v2;
    assert(v4.x == -3 && v4.y == -3 && v4.z == -3);

    Vector v5 = v1 * 2;
    assert(v5.x == 2 && v5.y == 4 && v5.z == 6);

    Vector v6 = v1 / 2;
    assert(v6.x == 0.5 && v6.y == 1 && v6.z == 1.5);

    v1 += v2;
    assert(v1.x == 5 && v1.y == 7 && v1.z == 9);

    v1 -= v2;
    assert(v1.x == 1 && v1.y == 2 && v1.z == 3);

    v1 *= 2;
    assert(v1.x == 2 && v1.y == 4 && v1.z == 6);

    v1 /= 2;
    assert(v1.x == 1 && v1.y == 2 && v1.z == 3);

    assert(v1 == Vector(1, 2, 3));
    assert(v1 != Vector(4, 5, 6));
}
