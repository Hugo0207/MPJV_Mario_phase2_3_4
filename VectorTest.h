#pragma once
#include "Vector.h"

class VectorTest {
public:
    void runTests();

private:
    void testConstructors();
    void testNorm();
    void testNormalize();
    void testScalarMul();
    void testAdd();
    void testSub();
    void testDotProduct();
    void testCrossProduct();
    void testOperators();
};
