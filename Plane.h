#pragma once
#include "Vector.h"

// Classe representant un plan grace a un point origine et un vecteur normal
class Plane
{
	public:

		Vector normalVector;
		Vector originPoint;
		float restitutionCoeff;

		// Constructors
		Plane();
		Plane(Vector normalVector, Vector originPoint, float restitutionCoeff);

		// Methods
		float signedDistanceTo(Vector vertex) const;
		Vector impactPoint(Vector vertex) const;
		void draw() const;
};

