#include "Collision.h"
#include "Plane.h"

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

// Met a jour le systeme de collision
// Detecte les collisions chaque couple de particule puis resout les collisions detectees
void Collision::update(std::vector<CorpsRigide*> corpsRigides, std::vector<Plane*> planes, float deltaTime) {
	for (auto cr1 = corpsRigides.begin(); cr1 != corpsRigides.end(); cr1++)
	{
		for (auto cr2 = cr1 + 1; cr2 != corpsRigides.end(); cr2++)
		{
			if (detect(*cr1, *cr2))
			{
				resolve(*cr1, *cr2);
			}
		}
	}

	for (auto cr = corpsRigides.begin(); cr != corpsRigides.end(); cr++)
	{
		Boite* box = dynamic_cast<Boite*>(*cr);
		if (box)
		{
			for (auto& plane : planes)
			{
				if (planeCollisionDetectBox(box, plane))
				{
					planeCollisionResolve(*cr, plane);
				}
			}
		}
	}
}

// Detecte la collision entre deux corps rigides donnees
bool Collision::detect(CorpsRigide* crA, CorpsRigide* crB) {
	// Verifier que crA et crB sont dans le meme octree (elargie)
	if (crA->getBoundingSphere()->currentOctree != crB->getBoundingSphere()->currentOctree)
	{
		return false;
	}

	// Verifier que les spheres englobantes de crA et crB collisionnent
	if (!crA->getBoundingSphere()->collides(crB->getBoundingSphere()))
	{
		return false;
	}

	// Verifier que les corps rigides (boites) collisionnent
	Boite* boxA = dynamic_cast<Boite*>(crA);
	Boite* boxB = dynamic_cast<Boite*>(crB);

	if (!boxA || !boxB) {
		return false;
	}

	// Axes a tester
	std::vector<Vector> axes;

	// Ajout des normales des faces de chaque boite, extractees depuis la matrice de transformation
	Matrice<4> transformA = boxA->getTransformMatrix();
	Matrice<4> transformB = boxB->getTransformMatrix();
	for (int i = 0; i < 3; ++i) {
		axes.push_back(transformA.getColumn(i));
		axes.push_back(transformB.getColumn(i));
	}

	// Ajout des produits vectoriels des aretes
	for (int i = 0; i < 3; ++i) {
		Vector edgeA = transformA.getColumn(i);
		for (int j = 0; j < 3; ++j) {
			Vector edgeB = transformB.getColumn(j);
			Vector crossProduct = edgeA.crossProduct(edgeB);
			if (crossProduct.norm() > 1e-6) {
				axes.push_back(crossProduct.normalize());
			}
		}
	}

	// Test de chaque axe
	for (const Vector& axis : axes) {
		// Projection des boites sur l'axe
		std::array<Vector, 8> verticesA = boxA->getTransformedVertices();
		std::array<Vector, 8> verticesB = boxB->getTransformedVertices();

		float minA = std::numeric_limits<float>::max();
		float maxA = std::numeric_limits<float>::lowest();
		for (const Vector& v : verticesA) {
			float projection = v.dotProduct(axis);
			minA = std::min(minA, projection);
			maxA = std::max(maxA, projection);
		}

		float minB = std::numeric_limits<float>::max();
		float maxB = std::numeric_limits<float>::lowest();
		for (const Vector& v : verticesB) {
			float projection = v.dotProduct(axis);
			minB = std::min(minB, projection);
			maxB = std::max(maxB, projection);
		}

		if (maxA < minB || maxB < minA) {
			// Si un axe de separation est trouvé, les boites ne collisionnent pas
			return false;
		}
	}

	// Pas d'axe de séparation, les boites collisionnent
	return true;
}

// Point d'impact entre deux particules entrant en collision
Vector Collision::impactPoint(Particle* pA, Particle* pB) {

	Vector impact;

	impact = pA->position + pA->position * pA->get_radius();

	return impact;
}

// Verifie si la collision trouvee est un contact au repos
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


// Separe les deux particules après la collision
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
* Resout une collision entre un couple de corps rigides a l'aide d'impulsions
*/
void Collision::resolve(CorpsRigide* cr1, CorpsRigide* cr2) {

	/*Vector normalVector = pA->normalVector(pB);

	Vector resultingVelocity = pA->velocity - pB->velocity;

	float impulsionMagnitude = ((restitutionCoeff + 1) * resultingVelocity.dotProduct(normalVector)) / (pA->getInverseMass() + pB->getInverseMass());

	pA->velocity = pA->velocity - ((normalVector * impulsionMagnitude) / pA->getMass());
	pB->velocity = pB->velocity + ((normalVector * impulsionMagnitude) / pB->getMass());*/
}

bool Collision::planeCollisionDetectBox(const Boite* box, const Plane* plane) {

	bool hasCrossed = false;

	// Recuperer les sommets transformes de la boite
	auto vertices = box->getTransformedVertices();

	if (plane->signedDistanceTo(vertices[0]) < 0)
	{
		hasCrossed = true;
	}

	for (const auto& vertex : vertices)
	{
		if ((plane->signedDistanceTo(vertex) < 0) != hasCrossed)
		{
			return true;
		}
	}
	return false;
}

float Collision::getPenetrationBoxPlane(const Boite* box, const Plane* plane)
{
	// Recuperer les sommets transformes de la boite
	auto vertices = box->getTransformedVertices();

	float max = 0;

	for (const auto& vertex : vertices)
	{
		float distanceTo = std::abs(plane->signedDistanceTo(vertex));
		distanceTo > max ? max = distanceTo : max = max;
	}

	return max;
}

void Collision::planeCollisionResolve(CorpsRigide* corpsRigide, Plane* plane) { 

	float penetration = 0.f;

	Boite* box = dynamic_cast<Boite*>(corpsRigide);
	if (box)
	{
		penetration = getPenetrationBoxPlane(box, plane);
	}

	Vector posCorpsRigide = corpsRigide->getPosition() + plane->normalVector * penetration;

	corpsRigide->setPosition(posCorpsRigide);

	float impulsionMagnitude = ((1.3) * corpsRigide->getLinearVelocity().dotProduct(plane->normalVector)) * corpsRigide->getMass();

	corpsRigide->setLinearVelocity(corpsRigide->getLinearVelocity() - ((plane->normalVector * impulsionMagnitude) / corpsRigide->getMass()));
}
