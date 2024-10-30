#pragma once
#include "Quaternion.h"

class QuaternionTest{
public:
    static void runTests();

private:
    static bool eq(float a, float b);
    static void testInverse();
    static void testNegate();
    static void testMultiply();
    static void testApplyRotation();
    static void testDifference();
    static void testDotProduct();
    static void testExponentiation();
    static void testGetters();
    static void testSetters();
    static void testConstructors();
};
