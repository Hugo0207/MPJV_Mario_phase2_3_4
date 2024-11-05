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
	float determinant() const {
		static_assert(N > 1, "La matrice doit être au moins 2x2 pour calculer un déterminant.");

		if constexpr (N == 2) {
			// Calcul du déterminant pour une matrice 2x2
			return values[0][0] * values[1][1] - values[0][1] * values[1][0];
		}
		else if constexpr (N == 3) {
			// Méthode de Sarrus pour une matrice 3x3
			return values[0][0] * (values[1][1] * values[2][2] - values[1][2] * values[2][1])
				- values[0][1] * (values[1][0] * values[2][2] - values[1][2] * values[2][0])
				+ values[0][2] * (values[1][0] * values[2][1] - values[1][1] * values[2][0]);
		}
		else {
			// Méthode par cofacteurs pour une matrice NxN (N > 3)
			float det = 0.0f;
			for (size_t j = 0; j < N; ++j) {
				det += ((j % 2 == 0) ? 1 : -1) * values[0][j] * cofacteur(0, j).determinant();
			}
			return det;
		}
	}

	//create a matrix by transping an other
	Matrice<N> transpose() const {
        Matrice<N> transposed;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                transposed.values[j][i] = values[i][j];
            }
        }
        return transposed;
    }

	//create a matrix by inversing an other
	Matrice<N> inverse() const {
		float det = determinant();
		if (det == 0) {
			throw std::invalid_argument("Le determinant doit être positif");
		}

		Matrice<N> adjugate; // Matrice adjointe
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				// calculing cofactor and transpose
				adjugate.values[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * cofactor(i, j).determinant();
			}
		}

		// divide by determinant to get the inverse
		Matrice<N> inverse;
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				inverse.values[i][j] = adjugate.values[i][j] / det;
			}
		}

		return inverse;
	}

	private : 
		Matrice<N - 1> cofacteur(size_t i, size_t j) const {
			Matrice<N - 1> minor;
			size_t minorRow = 0, minorCol = 0;
			for (size_t row = 0; row < N; ++row) {
				if (row == i) continue;
				minorCol = 0;
				for (size_t col = 0; col < N; ++col) {
					if (col == j) continue;
					minor.values[minorRow][minorCol] = values[row][col];
					minorCol++;
				}
				minorRow++;
			}
			return minor;
		}

};