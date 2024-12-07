#include "Boite.h"

Boite::Boite(float width, float height, float depth)
    : width(width), height(height), depth(depth)
{
    calculateDerivedData();

    // Creation de la sphere englobante
    createBoundingSphere();
}

void Boite::setDimensions(float width, float height, float depth)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    calculateDerivedData();
}

std::array<Vector, 8> Boite::getTransformedVertices() const
{
    std::array<Vector, 8> vertices;

    vertices[0] = Vector(-width / 2, -height / 2, -depth / 2);
    vertices[1] = Vector(-width / 2, -height / 2, depth / 2);
    vertices[2] = Vector(-width / 2, height / 2, -depth / 2);
    vertices[3] = Vector(-width / 2, height / 2, depth / 2);
    vertices[4] = Vector(width / 2, -height / 2, -depth / 2);
    vertices[5] = Vector(width / 2, -height / 2, depth / 2);
    vertices[6] = Vector(width / 2, height / 2, -depth / 2);
    vertices[7] = Vector(width / 2, height / 2, depth / 2);

    Matrice<4> transform = getTransformMatrix();
    for (auto& vertex : vertices)
    {
        vertex = transform * vertex;
    }

    return vertices;
}

void Boite::calculateDerivedData()
{
    CorpsRigide::calculateDerivedData();
}

void Boite::createBoundingSphere()
{
    this->boundingSphere = new Sphere(width*sqrt(3)/2, this->getPosition());
}
