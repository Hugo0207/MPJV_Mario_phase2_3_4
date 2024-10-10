#include "Collision.h"

Collision::Collision() {

}

// Met � jour le syst�me de collision
// D�tecte les collisions chaque couple de particule puis r�sout les collisions d�tect�es
void Collision::update(std::vector<Particle*> particles) {
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++)
	{
		for (auto it2 = it1 + 1; it2 != particles.end(); it2++)
		{
			if (detectionCollision(*it1, *it2))

			{
				(*it2)->velocity = Vector();
				(*it1)->velocity = Vector();

				Vector impact = impactPoint(*it1, *it2);

				resolveDetection(*it1, *it2);
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
bool Collision::detectionCollision(Particle* pA, Particle* pB) {
	float distanceCenter = pA->get_radius() + pB->get_radius();

	if (pA->distance(pB) <= distanceCenter)
	{
		return true;
	}
	return false;
}


// S�pare les deux particules apr�s la collision
float Collision::proportionalMove(Particle* pA, Particle* pB) {
	float penetration = (pA->get_radius() + pB->get_radius()) - pA->distance(pB);

	if (pB->getMass() > 0)
	{
		return (pB->getMass() / (pA->getMass() + 1 / pB->getMass())) * penetration;
	}
	else {
		return 0;
	}
}

/*
* postA = CA - N.(mB/mA+mB)
*/
void Collision::resolveDetection(Particle* pA, Particle* pB) {
	Vector normalVector = pA->normalVector(pB);

	Vector posA = pA->position - normalVector * proportionalMove(pA, pB);
	Vector posB = pB->position + normalVector * proportionalMove(pB, pA);


	pA->position = posA;
	pB->position = posB;
}
