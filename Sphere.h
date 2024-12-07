#pragma once
#include "Vector.h"

class OctreeNode;

class Sphere
{
	public:
		Vector center;
		float radius;
		OctreeNode* currentOctree;
		Sphere();
		Sphere(float radius, Vector center);
		bool collides(Sphere* otherSphere);
};

