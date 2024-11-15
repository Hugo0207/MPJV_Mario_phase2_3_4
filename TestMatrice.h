#pragma once

#include "./Matrice.h"

class TestMatrice
{
public:
	void RunTest();

private:

	void TestConstructor();
	void TestEqual();
	void TestCopy();
	void TestAdd();
	void TestMinus();
	void TestMultiplication();
	void TestScalarDivision();
	void TestDeterminant();
	void TestTranspose();
	void TestInverse();

};