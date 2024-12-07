#include "Sphere.h"
#include "OctreeNode.h"

Sphere::Sphere() : radius(0), center(Vector(0, 0, 0)), currentOctree(&OctreeNode())
{
}

Sphere::Sphere(float radius, Vector center)
    : radius(radius), center(center), currentOctree(&OctreeNode()) {}

bool Sphere::collides(Sphere* otherSphere)
{
    float distance = (this->center - otherSphere->center).norm();
    return distance < this->radius + otherSphere->radius;
}
