#include "Plane.h"

// Constructeurs
Plane::Plane() : normalVector(Vector(0, 0, 1)), originPoint(Vector(0, 0, 0)), restitutionCoeff(1.f)
{}
Plane::Plane(Vector normalVector, Vector originPoint, float restitutionCoeff) : 
normalVector(normalVector.normalize()),
originPoint(originPoint),
restitutionCoeff(restitutionCoeff)
{}

// Distance signee entre un point de l'espace et un plan
float Plane::signedDistanceTo(Vector vertex) const
{
	return normalVector.dotProduct(vertex - originPoint);
}

// Retourne le point d'impact potentiel sur le plan d'un point de l'espace
Vector Plane::impactPoint(Vector vertex) const
{
	Vector tn = normalVector * normalVector.dotProduct(vertex - originPoint);
	return vertex - tn;
}

// Dessine le plan
void Plane::draw() const
{
	ofPlanePrimitive plane;
	ofMaterial planeMat;

	planeMat.setShininess(64);
	planeMat.setDiffuseColor(ofColor(100, 100, 0)); // Jaune

	plane.setGlobalPosition(originPoint.toVec3());

	plane.set(30, 30); // Taille du plan, subdivisé en 100x100 pour une meilleure qualité de texture

	// Calcul de la rotation pour aligner à la normale du plan
	Vector defaultNormal(0, 0, 1); // Normale par défaut
	Vector axis = defaultNormal.crossProduct(normalVector).normalize(); // Axe de rotation
	float angle = acos(defaultNormal.dotProduct(normalVector)); // Angle de rotation en radians

	// On applique la rotation au plan
	plane.rotate(ofRadToDeg(angle), axis.x, axis.y, axis.z);

	planeMat.begin();

	// Dessine le sol
	plane.draw();

	// Termine le matériau
	planeMat.end();
}
