#pragma once
#include "Vector.h"
#include "QuaternionTest.h"

class Quaternion
{
private:
	float w;
	Vector xyzVector;

	// Constructeur utilis� pour les op�rations intra-classe
	static Quaternion* createQuat(float w, Vector xyzVector);

public:
	// Constructeur public
	Quaternion(float rotationAngle, Vector rotationAxis); // L'angle de rotation est attendu en degr�s

	// Norme du quaternion
	float norm() const;

	// Inverse/Conjugu� du quaternion, donne le m�me angle de rotation, mais avec une inversion du sens de rotation
	Quaternion* inverse() const;

	// N�gation du quaternion, donne le m�me d�placement angulaire
	Quaternion* negate() const;

	// Multiplication de deux quaternions
	Quaternion* multiply(Quaternion* other) const;

	// Application d'une rotation d�finie par ce quaternion � un vecteur
	Vector applyRotation(Vector* target) const;

	// Repr�sente le d�placement angulaire entre deux quaternions
	Quaternion* difference(Quaternion* other) const;

	// Produit scalaire, plus il est grand, plus les deux quaternions d�crivent des rotations similaires
	float dotProduct(Quaternion* other) const;

	// Exponentiation, repr�sente la fraction donn�e "t" du d�placement angulaire initiale
	Quaternion* exponentiation(float t) const;

	// Permet d'obtenir l'angle de la rotation repr�sent� par le quaternion (en degr�s)
	float getRotationAngle();

	// Permet d'obtenir l'axe de la rotation repr�sent� par le quaternion
	Vector getRotationAxis();

	// Permet de modifier l'angle de rotation repr�sent� par le quaternion (en degr�s)
	void setRotationAngle(float angle);

	// Permet de modifier l'axe de rotation repr�sent� par le quaternion
	void setRotationAxis(Vector axis);

	friend class QuaternionTest;

};

