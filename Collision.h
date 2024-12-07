#pragma once

#include "Vector.h"
#include "Particle.h"
#include "Boite.h"
#include "OctreeNode.h"
#include "CorpsRigide.h"
#include "OctreeNode.h"

class Collision
{
private:
	float restitutionCoeff;
	Vector gravity;


public:

	Collision(float restitutionCoeff, Vector gravity);

	void update(std::vector<CorpsRigide*> corpsRigides, std::vector<Plane*> planes, float deltaTime);

	bool detect(CorpsRigide* crA, CorpsRigide* crB);

	bool isRestContact(CorpsRigide* crA, CorpsRigide* crB, float deltaTime);

	void proportionalDetach(CorpsRigide* crA, CorpsRigide* crB);

	void resolve(CorpsRigide* pA, CorpsRigide* pB) const;

	bool planeCollisionDetectBox(const Boite* box, const Plane* plane);

	float getPenetrationBoxPlane(const Boite* box, const Plane* plane);

	void planeCollisionResolve(CorpsRigide* corpsRigide, Plane* plane);
};