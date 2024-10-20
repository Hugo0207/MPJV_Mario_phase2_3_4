#include "Collision.h"

Collision::Collision(float restitutionCoeff, Vector gravity) {
	if (restitutionCoeff >= 0 && restitutionCoeff <= 1)
	{
		this->restitutionCoeff = restitutionCoeff;
	}
	else
	{
		this->restitutionCoeff = 1;
	}

	gravity = gravity;
}

// Met � jour le syst�me de collision
// D�tecte les collisions chaque couple de particule puis r�sout les collisions d�tect�es
void Collision::update(std::vector<Particle*> particles, float deltaTime) {
	for (auto p1 = particles.begin(); p1 != particles.end(); p1++)
	{
		for (auto p2 = p1 + 1; p2 != particles.end(); p2++)
		{
			if (detect(*p1, *p2))
			{
				Vector impact = impactPoint(*p1, *p2);

				// On r�sout la collision ssi elle n'est pas d�tect�e au repos
				if (!isRestContact(*p1, *p2, deltaTime)) {
					resolve(*p1, *p2);
				}
			}
		}
	}
}

// Point d'impact entre deux particules entrant en collision
Vector Collision::impactPoint(Particle* pA, Particle* pB) {

	Vector impact;

	impact = pA->position + pA->position * pA->get_radius();

	return impact;
}

// D�tecte la collision entre deux particules donn�es
bool Collision::detect(Particle* pA, Particle* pB) {
	float distanceCenter = pA->get_radius() + pB->get_radius();

	if (pA->distance(pB) <= distanceCenter)
	{
		proportionalDetach(pA, pB);
		return true;
	}
	return false;
}

// V�rifie si la collision trouv�e est un contact au repos
bool Collision::isRestContact(Particle* pA, Particle* pB, float deltaTime)
{
	Vector normalVector = pA->normalVector(pB);
	Vector gravityProjectionToNormal = (gravity * deltaTime).projectTo(normalVector);
	Vector p1VelocityProjectionToNormal = pA->velocity.projectTo(normalVector);
	Vector p2VelocityProjectionToNormal = pB->velocity.projectTo(normalVector);

	bool isP1Stationary = p1VelocityProjectionToNormal.norm() < gravityProjectionToNormal.norm();
	bool isP2Stationary = p2VelocityProjectionToNormal.norm() < gravityProjectionToNormal.norm();

	return isP1Stationary && isP2Stationary;
}


// S�pare les deux particules apr�s la collision
void Collision::proportionalDetach(Particle* pA, Particle* pB) {
	float penetration = (pA->get_radius() + pB->get_radius()) - pA->distance(pB);

	float separationMagnitude = 0;

	if (pB->getMass() > 0)
	{
		separationMagnitude = (pB->getMass() / (pA->getMass() + 1 / pB->getMass())) * penetration;
	}
	 
	Vector normalVector = pA->normalVector(pB);

	Vector posA = pA->position - normalVector * separationMagnitude;
	Vector posB = pB->position + normalVector * separationMagnitude;


	pA->position = posA;
	pB->position = posB;
}

/*
* R�sout une collision entre un couple de particule � l'aide d'impulsions
*/
void Collision::resolve(Particle* pA, Particle* pB) {

	Vector normalVector = pA->normalVector(pB);

	Vector resultingVelocity = pA->velocity - pB->velocity;

	float impulsionMagnitude = ((restitutionCoeff + 1) * resultingVelocity.dotProduct(normalVector)) / (pA->getInverseMass() + pB->getInverseMass());

	pA->velocity = pA->velocity - ((normalVector * impulsionMagnitude) / pA->getMass());
	pB->velocity = pB->velocity + ((normalVector * impulsionMagnitude) / pB->getMass());
}
