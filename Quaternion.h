#pragma once
#include "Vector.h"
#include "QuaternionTest.h"

class Quaternion
{
private:
	float w;
	Vector xyzVector;

	// Constructeur utilisé pour les opérations intra-classe
	static Quaternion* createQuat(float w, Vector xyzVector);

public:
	// Constructeur public
	Quaternion(float rotationAngle, Vector rotationAxis); // L'angle de rotation est attendu en degrés

	// Norme du quaternion
	float norm() const;

	// Inverse/Conjugué du quaternion, donne le même angle de rotation, mais avec une inversion du sens de rotation
	Quaternion* inverse() const;

	// Négation du quaternion, donne le même déplacement angulaire
	Quaternion* negate() const;

	// Multiplication de deux quaternions
	Quaternion* multiply(Quaternion* other) const;

	// Application d'une rotation définie par ce quaternion à un vecteur
	Vector applyRotation(Vector* target) const;

	// Représente le déplacement angulaire entre deux quaternions
	Quaternion* difference(Quaternion* other) const;

	// Produit scalaire, plus il est grand, plus les deux quaternions décrivent des rotations similaires
	float dotProduct(Quaternion* other) const;

	// Exponentiation, représente la fraction donnée "t" du déplacement angulaire initiale
	Quaternion* exponentiation(float t) const;

	// Permet d'obtenir l'angle de la rotation représenté par le quaternion (en degrés)
	float getRotationAngle();

	// Permet d'obtenir l'axe de la rotation représenté par le quaternion
	Vector getRotationAxis();

	// Permet de modifier l'angle de rotation représenté par le quaternion (en degrés)
	void setRotationAngle(float angle);

	// Permet de modifier l'axe de rotation représenté par le quaternion
	void setRotationAxis(Vector axis);

	friend class QuaternionTest;

};

