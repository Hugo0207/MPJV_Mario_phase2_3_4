#pragma once
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Vector.h"

template <size_t N>
class Matrice
{
public:
    float values[N][N];

    // Constructeur par défaut
    Matrice() {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                values[i][j] = 0.0f;
            }
        }
    }

    // Constructeur avec liste d'initialisation
    Matrice(std::initializer_list<float> initList) {
        auto it = initList.begin();
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                values[i][j] = (it != initList.end()) ? *it++ : 0.0f;
            }
        }
    }

    // Constructeur de copie
    Matrice(const Matrice& other)
    {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                values[i][j] = other.values[i][j];
            }
        }
    }

    // Opérateur d'affichage
    friend std::ostream& operator<<(std::ostream& os, const Matrice& mat) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                os << mat.values[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    // Opérateur d'égalité
    bool operator==(Matrice& other) {
        bool IsEqual = true;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (this->values[i][j] != other.values[i][j]) IsEqual = false;
            }
            return IsEqual;
        }
    }

    // Opérateur d'inégalité
    bool operator!=(const Matrice& other) const {
        return !(*this == other);
    }

    // Opérateurs d'affectation composés avec une autre matrice
    Matrice& operator+=(const Matrice& other)
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] += other.values[i][j];
            }
        }
        return *this;
    }

    Matrice& operator-=(const Matrice& other)
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] -= other.values[i][j];
            }
        }
        return *this;
    }

    // Opérateurs d'addition et de soustraction avec une autre matrice
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

    // Opérateurs avec un scalaire

    /*Matrice& operator*=(float scalar) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] *= scalar;
            }
        }
        return *this;
    }*/

    Matrice& operator*(float scalar)
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] *= scalar;
            }
        }
        return *this;
    }

    /*Matrice& operator/=(float scalar) {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division par zéro non autorisée.");
        }
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] /= scalar;
            }
        }
        return *this;
    }*/

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

    // Opérateurs d'addition et de soustraction avec un scalaire
    Matrice operator+(float scalar) const
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                m.values[i][j] += scalar;
            }
        }
        return *this;
    }

    Matrice operator-(float scalar) const
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                m.values[i][j] -= scalar;
            }
        }
        return *this;
    }

    // Opérateur de multiplication matricielle
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


    // Opérateur de multiplication matrice-vecteur
    Vector operator*(const Vector& vec) const
    {
        static_assert(N == 3 || N == 4, "Cette opération est définie uniquement pour N = 3 ou N = 4.");
        Vector result;
        if constexpr (N == 3)
        {
            result.x = values[0][0] * vec.x + values[0][1] * vec.y + values[0][2] * vec.z;
            result.y = values[1][0] * vec.x + values[1][1] * vec.y + values[1][2] * vec.z;
            result.z = values[2][0] * vec.x + values[2][1] * vec.y + values[2][2] * vec.z;
        }
        else if constexpr (N == 4)
        {
            result.x = values[0][0] * vec.x + values[0][1] * vec.y + values[0][2] * vec.z + values[0][3];
            result.y = values[1][0] * vec.x + values[1][1] * vec.y + values[1][2] * vec.z + values[1][3];
            result.z = values[2][0] * vec.x + values[2][1] * vec.y + values[2][2] * vec.z + values[2][3];
        }
        return result;
    }
    /*Vector operator*(const Vector& vec) const
    {
        static_assert(N == 3, "Cette opération est définie uniquement pour N = 3.");
        Vector result;
        result.x = values[0][0] * vec.x + values[0][1] * vec.y + values[0][2] * vec.z;
        result.y = values[1][0] * vec.x + values[1][1] * vec.y + values[1][2] * vec.z;
        result.z = values[2][0] * vec.x + values[2][1] * vec.y + values[2][2] * vec.z;
        return result;
    }*/


    // Calcul du déterminant
    float determinant() const{
            
        if (N == 1) return values[0][0];
        if (N == 2) return values[0][0] * values[1][1] - values[0][1] * values[1][0];

        float det = 0;

        for (size_t col = 0; col < N; col++)
        {
            float cofactor = (col % 2 == 0 ? 1 : -1) * values[0][col];

            det += cofactor * getSubMatrix(0, col).determinant();
        }
        return det;
    }

    // Transposée de la matrice
    Matrice<N> transpose() const {
        Matrice<N> transposed;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                transposed.values[j][i] = this->values[i][j];
            }
        }
        return transposed;
    }

    // Inverse de la matrice
    Matrice<N> inverse() const{
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

    Vector getColumn(size_t col) const {
        static_assert(N == 4, "Column extraction is valid only for 4x4 matrices.");
        if (col >= N) {
            throw std::out_of_range("Column index out of range.");
        }
        return Vector(values[0][col], values[1][col], values[2][col]);
    }

private:
    // get a subMatrix in deleting a row and a colonne
    Matrice<N - 1> getSubMatrix(int skipRow, int skipCol) const{
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

    Matrice<N> cofactorMatrix() const{
        Matrice<N> cofactorMatrix;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cofactorMatrix.values[i][j] = (i + j) % 2 == 0 ? getSubMatrix(i, j).determinant() : -getSubMatrix(i, j).determinant();
            }
        }
        return cofactorMatrix;
    }

    /* Calcul du cofacteur pour les matrices de taille N > 1
    Matrice<N - 1> cofacteur(size_t row_to_remove, size_t col_to_remove) const {
        Matrice<N - 1> minor;
        size_t minorRow = 0;
        for (size_t i = 0; i < N; ++i) {
            if (i == row_to_remove) continue;
            //size_t minorCol = 0;
            for (size_t j = 0; j < N; ++j) {
                if (j == col_to_remove) continue;
                minor.values[minorRow][minorCol] = values[i][j];
                minorCol++;
            }
            minorRow++;
        }
        return minor;
    }*/
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