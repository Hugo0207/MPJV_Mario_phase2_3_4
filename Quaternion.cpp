#include "Quaternion.h"

// Constructeur public
Quaternion::Quaternion(float rotationAngle, Vector rotationAxis)
{
	float halfRotationAngleRad = (rotationAngle * PI / 180) / 2;
	w = cos(halfRotationAngleRad);
	xyzVector = rotationAxis * halfRotationAngleRad;
}

// Constructeur utilis� pour les op�rations intra-classe
Quaternion::Quaternion(float w, Vector xyzVector)
{
	w = w;
	xyzVector = xyzVector;
}

// Inverse/Conjugu� du quaternion, donne le m�me angle de rotation, mais avec une inversion du sens de rotation
Quaternion* Quaternion::inverse() const
{
	return new Quaternion(w, xyzVector * (-1));
}

// N�gation du quaternion, donne le m�me d�placement angulaire
Quaternion* Quaternion::negate() const
{
	return new Quaternion(-w, xyzVector * (-1));
}

// Multiplication de deux quaternions
Quaternion* Quaternion::multiply(Quaternion* other) const
{
	float resW = w * other->w;
	float dotProduct = (xyzVector * (-1)).dotProduct(other->xyzVector);
	Vector resXYZvector = ((other->xyzVector * w) + (xyzVector * other->w) + (xyzVector.crossProduct(other->xyzVector))) * dotProduct;

	return new Quaternion(resW, resXYZvector);
}

// Application d'une rotation d�finie par ce quaternion � un vecteur
Vector Quaternion::applyRotation(Vector* target) const
{
	Quaternion* targetQuaternion = new Quaternion(0, *target);
	Quaternion* resultQuaternion = (this->multiply(targetQuaternion))->multiply(this->inverse());

	return resultQuaternion->xyzVector;
}

// Repr�sente le d�placement angulaire entre deux quaternions
Quaternion* Quaternion::difference(Quaternion* other) const
{
	return other->multiply(this->inverse());
}

// Produit scalaire, plus il est grand, plus les deux quaternions d�crivent des rotations similaires
float Quaternion::dotProduct(Quaternion* other) const
{
	return w*other->w + xyzVector.x*other->xyzVector.x + xyzVector.y * other->xyzVector.y + xyzVector.z * other->xyzVector.z;
}

// Exponentiation, repr�sente la fraction donn�e "t" du d�placement angulaire initiale
Quaternion* Quaternion::exponentiation(float t) const
{
	float halfTheta = acos(w);
	return new Quaternion(cos(t * halfTheta), xyzVector * (sin(t * halfTheta)/sin(halfTheta)));
}

// Permet d'obtenir l'angle de la rotation repr�sent� par le quaternion (en degr�s)
float Quaternion::getRotationAngle()
{
	return (2*acos(w)) * 180/PI;
}

// Permet d'obtenir l'axe de la rotation repr�sent� par le quaternion
Vector Quaternion::getRotationAxis()
{
	float halfRotationAngleRad = (getRotationAngle() * PI / 180) / 2;
	return xyzVector / sin(halfRotationAngleRad);
}

// Permet de modifier l'angle de rotation repr�sent� par le quaternion (en degr�s)
void Quaternion::setRotationAngle(float newAngle)
{
	float halfRotationAngleRad = (newAngle * PI / 180) / 2;
	w = cos(halfRotationAngleRad);
	xyzVector = getRotationAxis() * halfRotationAngleRad;
}

// Permet de modifier l'axe de rotation repr�sent� par le quaternion
void Quaternion::setRotationAxis(Vector newAxis)
{
	float halfRotationAngleRad = (getRotationAngle() * PI / 180) / 2;
	w = cos(halfRotationAngleRad);
	xyzVector = newAxis * halfRotationAngleRad;
}
