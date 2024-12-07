#pragma once
#include "Vector.h"

class OctreeNode;

// Classe representant une sphere
class Sphere
{
	public:
		Vector center;
		float radius;
		OctreeNode* currentOctree;
		Sphere();
		Sphere(float radius, Vector center);
		bool collides(Sphere* otherSphere);
		float distanceTo(Sphere* otherSphere) const;
};

