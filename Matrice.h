#pragma once
#include <initializer_list>
#include <iostream>

template <size_t N>
class Matrice
{
public :
	float values[N][N];

	Matrice() {
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				values[i][j] = 0.0f;
			}
		}
	}

	Matrice(std::initializer_list<float> initList) {
		auto it = initList.begin();
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				values[i][j] = (it != initList.end()) ? *it++ : 0.0f;
			}
		}
	}

	//copy constructor
	Matrice(const Matrice & other)
	{
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				values[i][j] = other.values[i][j];
			}
		}
	}

	//redefinition of << operator to print the matrice
	friend std::ostream& operator<<(std::ostream& os, const Matrice& mat) {
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				os << mat.values[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}

	//compare if two matrix are equal
	bool operator==(Matrice& other) {
		bool IsEqual = true;
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				if (this->values[i][j] != other.values[i][j]) IsEqual = false;
			}
			return IsEqual;
		}
	}

	//add a matrix to another
	Matrice&  operator+=(const Matrice &other)
	{
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				this->values[i][j] += other.values[i][j];
			}
		}
		return *this;
	}

	//minus a matrix to another
	Matrice& operator-=(const Matrice &other)
	{
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				this->values[i][j] -= other.values[i][j];
			}
		}
		return *this;
	}

	//creating new matrix in adding two other
	Matrice operator+(const Matrice& other) const
	{
		Matrice<N> m;
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				m.values[i][j] = this->values[i][j] + other.values[i][j];
			}
		}
		return m;
	}

	//add a scalar to a matrix
	Matrice operator+(float scalar) const
	{
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				m.values[i][j] += scalar;
			}
		}
		return *this;
	}

	//creating new matrix in minus two other
	Matrice operator-(const Matrice& other) const
	{
		Matrice<N> m;
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				m.values[i][j] = this->values[i][j] - other.values[i][j];
			}
		}
		return m;
	}

	//minus a scalar to a matrix
	Matrice operator-(float scalar) const
	{
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				m.values[i][j] -= scalar;
			}
		}
		return *this;
	}

	//creating a new matrix multipling two other
	Matrice operator*(const Matrice& other) const
	{
		Matrice<N> m;
		float value = 0;
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				for (size_t k = 0; k < N; k++) {
					value += this->values[i][k] * other.values[k][j];
				}
				m.values[i][j] = value;
				value = 0;
			}
		}
		return m;
	}

	//multipling matrix by a scalar
	Matrice& operator*(float scalar)
	{
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				this->values[i][j] *= scalar;
			}	
		}
		return *this;
	}

	//dividing a matri by a scalar
	Matrice& operator/(float scalar)
	{
		if (scalar == 0) {	
			throw std::invalid_argument("Vous ne pouvez pas diviser par 0");
		}

		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				this->values[i][j] /= scalar;
			}
		}
		return *this;
	}
	
	//get the determinant of a matrix
	float determinant() {

		if  (N == 1) return values[0][0];
		if  (N == 2) return values[0][0] * values[1][1] - values[0][1] * values[1][0];

		float det = 0;

		for (size_t col = 0; col < N; col++)
		{
			float cofactor = (col % 2 == 0 ? 1 : -1) * values[0][col];

			det += cofactor * getSubMatrix(0, col).determinant();
		}

		return det;
	}

	

	//create a matrix by transping an other
	Matrice<N> transpose() const {
        Matrice<N> transposed;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                transposed.values[j][i] = this->values[i][j];
            }
        }
        return transposed;
    }

	//create a matrix by inversing an other
	Matrice<N> inverse() {
		float det = determinant();
		if (det == 0) {
			throw std::invalid_argument("La matrice est singulière, elle n'a pas d'inverse.");
		}

		Matrice<N> cofactorMatrix = this->cofactorMatrix();
		Matrice<N> adjugateMatrix = cofactorMatrix.transpose();

		Matrice<N> inverseMatrix;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				inverseMatrix.values[i][j] = adjugateMatrix.values[i][j] / det;
			}
		}

		return inverseMatrix;
	}

	private : 
		// get a subMatrix in deleting a row and a colonne
		Matrice<N - 1> getSubMatrix(int skipRow, int skipCol)
		{
			Matrice<N - 1> subMatrix;

			int r = 0;
			for (size_t i = 0; i < N; i++)
			{
				if (i == skipRow) continue;

				int c = 0;
				for (size_t j = 0; j < N; j++)
				{
					if (j == skipCol) continue;
					subMatrix.values[r][c] = values[i][j];

					c++;
				}
				r++;
			}
			return subMatrix;
		}

		Matrice<N> cofactorMatrix() {
			Matrice<N> cofactorMatrix;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					cofactorMatrix.values[i][j] = (i + j) % 2 == 0 ? getSubMatrix(i, j).determinant() : -getSubMatrix(i, j).determinant();
				}
			}
			return cofactorMatrix;
		}

};

template <>
class Matrice<1>
{
public:
	float values[1][1];

	float determinant() const {
		return values[0][0];
	}
};