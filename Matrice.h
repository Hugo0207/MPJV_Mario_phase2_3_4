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
    Matrice(const Matrice& other) {
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
    bool operator==(const Matrice& other) const {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (this->values[i][j] != other.values[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // Opérateur d'inégalité
    bool operator!=(const Matrice& other) const {
        return !(*this == other);
    }

    // Opérateurs d'affectation composés avec une autre matrice
    Matrice& operator+=(const Matrice& other) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] += other.values[i][j];
            }
        }
        return *this;
    }

    Matrice& operator-=(const Matrice& other) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] -= other.values[i][j];
            }
        }
        return *this;
    }

    // Opérateurs d'addition et de soustraction avec une autre matrice
    Matrice operator+(const Matrice& other) const {
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = this->values[i][j] + other.values[i][j];
            }
        }
        return result;
    }

    Matrice operator-(const Matrice& other) const {
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = this->values[i][j] - other.values[i][j];
            }
        }
        return result;
    }

    // Opérateurs avec un scalaire
    Matrice& operator*=(float scalar) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrice operator*(float scalar) const {
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = this->values[i][j] * scalar;
            }
        }
        return result;
    }

    Matrice& operator/=(float scalar) {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division par zéro non autorisée.");
        }
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->values[i][j] /= scalar;
            }
        }
        return *this;
    }

    Matrice operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division par zéro non autorisée.");
        }
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = this->values[i][j] / scalar;
            }
        }
        return result;
    }

    // Opérateurs d'addition et de soustraction avec un scalaire
    Matrice operator+(float scalar) const {
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = this->values[i][j] + scalar;
            }
        }
        return result;
    }

    Matrice operator-(float scalar) const {
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = this->values[i][j] - scalar;
            }
        }
        return result;
    }

    // Opérateur de multiplication matricielle
    Matrice operator*(const Matrice& other) const {
        Matrice<N> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result.values[i][j] = 0.0f;
                for (size_t k = 0; k < N; k++) {
                    result.values[i][j] += this->values[i][k] * other.values[k][j];
                }
            }
        }
        return result;
    }


	// Opérateur de multiplication matrice-vecteur
    Vector operator*(const Vector& vec) const
    {
        static_assert(N == 3, "Cette opération est définie uniquement pour N = 3.");
        Vector result;
        result.x = values[0][0] * vec.x + values[0][1] * vec.y + values[0][2] * vec.z;
        result.y = values[1][0] * vec.x + values[1][1] * vec.y + values[1][2] * vec.z;
        result.z = values[2][0] * vec.x + values[2][1] * vec.y + values[2][2] * vec.z;
        return result;
    }


    // Calcul du déterminant
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
                float sign = ((j % 2 == 0) ? 1.0f : -1.0f);
                det += sign * values[0][j] * cofacteur(0, j).determinant();
            }
            return det;
        }
    }

    // Transposée de la matrice
    Matrice<N> transpose() const {
        Matrice<N> transposed;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                transposed.values[j][i] = values[i][j];
            }
        }
        return transposed;
    }

    // Inverse de la matrice
    Matrice<N> inverse() const {
        float det = determinant();
        if (det == 0.0f) {
            throw std::invalid_argument("Le déterminant est nul; la matrice n'est pas inversible.");
        }

        Matrice<N> adjugate; // Matrice adjointe (transposée de la comatrice)
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                adjugate.values[j][i] = sign * cofacteur(i, j).determinant(); // Notez l'indice [j][i] pour la transposée
            }
        }

        // Division par le déterminant
        Matrice<N> inverse;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                inverse.values[i][j] = adjugate.values[i][j] / det;
            }
        }

        return inverse;
    }

private:
    // Calcul du cofacteur pour les matrices de taille N > 1
    Matrice<N - 1> cofacteur(size_t row_to_remove, size_t col_to_remove) const {
        Matrice<N - 1> minor;
        size_t minorRow = 0;
        for (size_t i = 0; i < N; ++i) {
            if (i == row_to_remove) continue;
            size_t minorCol = 0;
            for (size_t j = 0; j < N; ++j) {
                if (j == col_to_remove) continue;
                minor.values[minorRow][minorCol] = values[i][j];
                minorCol++;
            }
            minorRow++;
        }
        return minor;
    }
};
