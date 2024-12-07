#pragma once
#include "Vector.h"

class Plane
{
	public:
		Vector normalVector;
		Vector originPoint;

		// Constructors
		Plane();
		Plane(Vector normalVector, Vector originPoint);

		// Methods
		float signedDistanceTo(Vector vertex) const;
		Vector impactPoint(Vector vertex) const;
		void draw() const;
};

