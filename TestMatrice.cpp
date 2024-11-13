#include "TestMatrice.h"
#include <cassert>

void TestMatrice::RunTest()
{
	TestConstructor();
	TestEqual();
	TestCopy();
	TestAdd();
	TestMinus();
	TestMultiplication();
	TestScalarDivision();
	TestDeterminant();
	TestTranspose();
	TestInverse();
	std::cout << "Test of matrix pass with sucess" << std::endl;
}

void TestMatrice::TestConstructor()
{
	Matrice<2> A{};
	Matrice<3> B{1,2,3,4,5,6,7,8,9};
	Matrice<3> C{ 1,2,3,4,5 };


	//test A
	assert((A.values[0][0] == 0) && (A.values[0][1] == 0) && (A.values[1][0] == 0) && (A.values[1][1] == 0));
	
	//test B
	assert((B.values[0][0] == 1) && (B.values[0][1] == 2) && (B.values[0][2] == 3));
	assert((B.values[1][0] == 4) && (B.values[1][1] == 5) && (B.values[1][2] == 6));
	assert((B.values[2][0] == 7) && (B.values[2][1] == 8) && (B.values[2][2] == 9));

	//test B
	assert((C.values[0][0] == 1) && (C.values[0][1] == 2) && (C.values[0][2] == 3));
	assert((C.values[1][0] == 4) && (C.values[1][1] == 5) && (C.values[1][2] == 0));
	assert((C.values[2][0] == 0) && (C.values[2][1] == 0) && (C.values[2][2] == 0));

}

void TestMatrice::TestEqual()
{
	Matrice<3> A{ 1,2,3,4,5,6,7,8,9 };
	Matrice<3> B{ 1,2,3,4,5,6,7,8,9 };
	Matrice<3> C{};

	assert(A == B);
	assert(!(A == C));
}

void TestMatrice::TestCopy()
{
	Matrice<3> A{ 1,2,3,4,5,6,7,8,9 };

	Matrice<3> B(A);
	
	assert(A == B);
}

void TestMatrice::TestAdd()
{
	Matrice<3> A{ 1,2,3,4,5,6,7,8,9 };
	Matrice<3> B{ 1,2,3,4,5,6,7,8,9 };
	Matrice<3> C{2,4,6,8,10,12,14,16,18};
	Matrice<3> D{};

	A += D;
	assert(A == B);

	D = A + B;
	assert(D == C);

	A += B;
	assert(A == C);
}

void TestMatrice::TestMinus()
{
	Matrice<3> A{1,2,3,4,5,6,7,8,9};
	Matrice<3> B{1,2,3,4,5,6,7,8,9};
	Matrice<3> C{};

	A -= C;
	assert(A == B);

	Matrice<3> D = A - B;
	assert(D == C);
	
	A -= B;
	assert(A == C);
}

void TestMatrice::TestMultiplication()
{

	//matrix multiplication
	Matrice<4> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	Matrice<4> double_A{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 };
	Matrice<4> B{ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	Matrice<4> C{ 80, 70, 60, 50, 240, 214, 188, 162, 400, 358, 316, 274, 560, 502, 444, 386 };
	Matrice<4> D;

	D = A * B;

	assert(D == C);

	//scalar multiplication 
	A * 2;
	assert(A == double_A);
}

void TestMatrice::TestScalarDivision()
{
	Matrice<4> double_A{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 };
	Matrice<4> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	
	double_A / 2;
	assert(double_A == A);

	try {
		A / 0;
		assert(false);
	}
	catch (const std::invalid_argument& e)
	{
		assert(true);
	}

}

void TestMatrice::TestDeterminant()
{
	Matrice<4> A{ 2, 3, 1, 4, 1, 5, 7, 6, 4, 8, 9, 2, 3, 7, 5, 1 };
	float det = A.determinant();


	assert(det == -247);

}

void TestMatrice::TestTranspose()
{
	Matrice<4> A{ 2, 3, 1, 4, 1, 5, 7, 6, 4, 8, 9, 2, 3, 7, 5, 1 };
	Matrice<4> AT{ 2, 1, 4, 3, 3, 5, 8, 7, 1, 7, 9, 5, 4, 6, 2, 1 };
	Matrice<4> transpose = A.transpose();

	assert(transpose == AT);

}

void TestMatrice::TestInverse()
{
	Matrice<4> A{ 1, 2, 3, 4, 2, 5, 4, 3, 3, 4, 5, 2, 4, 3, 2, 1 };

	Matrice<4> Ainverse{ 1.0f / 10, -1.0f / 4, 0.0f, 7.0f / 20,
						-1.0f / 4, 1.0f / 2, -1.0f / 4, 0.0f,
						0.0f, -1.0f / 4, 1.0f / 2, -1.0f / 4,
						7.0f / 20, 0.0f, -1.0f / 4, 1.0f / 10 };

	Matrice<4> inverse = A.inverse();

	assert(inverse == Ainverse);
}
