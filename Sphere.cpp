#include "Sphere.h"
#include "OctreeNode.h"

// Constructeurs
Sphere::Sphere() : radius(0), center(Vector(0, 0, 0)), currentOctree(&OctreeNode())
{
}
Sphere::Sphere(float radius, Vector center)
    : radius(radius), center(center), currentOctree(&OctreeNode()) {}

// Verifie la collision entre deux spheres
bool Sphere::collides(Sphere* otherSphere)
{
    float distance = (this->center - otherSphere->center).norm();
    return distance < this->radius + otherSphere->radius;
}

// Retourne la distance entre deux spheres
float Sphere::distanceTo(Sphere* otherSphere) const
{
    float distance = (this->center - otherSphere->center).norm();
    return distance;
}
