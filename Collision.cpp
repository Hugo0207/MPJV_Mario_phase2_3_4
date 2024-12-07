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
				// On resout la collision ssi elle n'est pas detectee au repos
				if (!isRestContact(*cr1, *cr2, deltaTime)) {
					resolve(*cr1, *cr2);
				}
			}
		}
	}

	for (auto cr = corpsRigides.begin(); cr != corpsRigides.end(); cr++)
	{
		// Cas d'une boite
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

	// SAT
	// Axes a tester
	std::vector<Vector> axes;
	// Ajout des normales des faces de chaque boite, extraites depuis la matrice de transformation
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

	// Pas d'axe de séparation, les boites collisionnent, on separe les boites
	proportionalDetach(crA, crB);
	return true;
}

// Verifie si la collision trouvee est un contact au repos
bool Collision::isRestContact(CorpsRigide* crA, CorpsRigide* crB, float deltaTime)
{
	Vector normalVector = crA->getNormalVector(crB);
	Vector gravityProjectionToNormal = (gravity * deltaTime).projectTo(normalVector);
	Vector crAVelocityProjectionToNormal = crA->getLinearVelocity().projectTo(normalVector);
	Vector crBVelocityProjectionToNormal = crB->getLinearVelocity().projectTo(normalVector);

	bool isCrAStationary = crAVelocityProjectionToNormal.norm() < gravityProjectionToNormal.norm();
	bool isCr2Stationary = crBVelocityProjectionToNormal.norm() < gravityProjectionToNormal.norm();

	return isCrAStationary && isCr2Stationary;
}


// Separe les deux corps rigides après la collision
void Collision::proportionalDetach(CorpsRigide* crA, CorpsRigide* crB) {

	Sphere* boundingSphereA = crA->getBoundingSphere();
	Sphere* boundingSphereB = crB->getBoundingSphere();

	float penetration = (boundingSphereA->radius + boundingSphereB->radius) - boundingSphereA->distanceTo(boundingSphereB);

	float separationMagnitude = 0;

	if (crB->getMass() > 0)
	{
		separationMagnitude = (crB->getMass() / (crA->getMass() + 1 / crB->getMass())) * penetration;
	}

	Vector normalVector = crA->getNormalVector(crB);

	Vector posA = crA->getPosition() - normalVector * separationMagnitude;
	Vector posB = crB->getPosition() + normalVector * separationMagnitude;


	crA->setPosition(posA);
	crB->setPosition(posB);
}

/*
* Resout une collision entre un couple de corps rigides a l'aide d'impulsions
*/
void Collision::resolve(CorpsRigide* cr1, CorpsRigide* cr2) const {

	Vector normalVector = cr1->getNormalVector(cr2);

	Vector resultingVelocity = cr1->getLinearVelocity() - cr2->getLinearVelocity();

	float impulsionMagnitude = ((restitutionCoeff + 1) * resultingVelocity.dotProduct(normalVector)) / ((1 / cr1->getMass()) + (1 / cr2->getMass()));

	cr1->setLinearVelocity(cr1->getLinearVelocity() - ((normalVector * impulsionMagnitude) / cr1->getMass()));
	cr2->setLinearVelocity(cr2->getLinearVelocity() + ((normalVector * impulsionMagnitude) / cr2->getMass()));
}

// Verifie la collision entre une boite et un plan
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

// Rend la distance de penetration signee entre uen boite et un plan
float Collision::getPenetrationBoxPlane(const Boite* box, const Plane* plane)
{
	// Recuperer les sommets transformes de la boite
	auto vertices = box->getTransformedVertices();
	auto negativeDist = std::vector<float>();
	auto positiveDist = std::vector<float>();

	// On remplit les listes des distances positives et negatives
	for (const auto& vertex : vertices)
	{
		float signedDistanceTo = plane->signedDistanceTo(vertex);
		float distanceTo = std::abs(signedDistanceTo);
		signedDistanceTo < 0 ? negativeDist.push_back(distanceTo) : positiveDist.push_back(distanceTo);
	}

	// On parcourt la liste la plus petite et on retourne la distance signee entre le sommet le plus penetrant et le plan
	float max = 0;
	if (positiveDist.size() >= negativeDist.size())
	{
		for (const auto& dist : negativeDist)
		{
			dist > max? max = -dist : max = max;
		}
	}
	else
	{
		for (const auto& dist : positiveDist)
		{
			dist > max ? max = dist : max = max;
		}
	}
	return max;
}

// Resout la collision en tre un plan et un corps rigide
void Collision::planeCollisionResolve(CorpsRigide* corpsRigide, Plane* plane) { 

	float penetration = 0.f;

	// Cas d'une boite
	Boite* box = dynamic_cast<Boite*>(corpsRigide);
	if (box)
	{
		penetration = getPenetrationBoxPlane(box, plane);
	}

	Vector posCorpsRigide = corpsRigide->getPosition() - plane->normalVector * penetration;

	corpsRigide->setPosition(posCorpsRigide);

	float impulsionMagnitude = ((1 + plane->restitutionCoeff) * corpsRigide->getLinearVelocity().dotProduct(plane->normalVector)) * corpsRigide->getMass();

	corpsRigide->setLinearVelocity(corpsRigide->getLinearVelocity() - ((plane->normalVector * impulsionMagnitude) / corpsRigide->getMass()));

	// Si la vitesse est en dessous de 0.1, on arrete l'objet
	if (corpsRigide->getLinearVelocity().norm() < 0.1)
	{
		corpsRigide->setLinearVelocity(Vector(0, 0, 0));
	}
}
