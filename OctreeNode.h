#pragma once

#include "Vector.h"

class Object {
public:
	Vector center; 
	float radius;
	Object(Vector center, float radius);
};


//Box representing the space of the world that will be devise un smaller box if needs
class BoundingBox {

public : 
	Vector m_min, m_max;

	BoundingBox() : m_min(Vector()), m_max(Vector()) {}
	BoundingBox(const Vector& min, const Vector& max);

	//
	bool IsContainingObject(Object* object);
};


//node of the octree
class OctreeNode
{
public :

	OctreeNode(const BoundingBox& bounds);

	//Insert an object in the node
	void Insert(Object* obj);

	//display all informations of the OctreeNode and its childs
	void Display(int depth = 0);

private :
	//box representing this node
	BoundingBox m_bounds;

	//objects contain in this node
	std::vector<Object*> m_objects;

	//childs of this node
	OctreeNode* children[8];

	static const int MAX_OBJECTS = 2;

	void Distribute(Object* obj);

	void Split();
};


/* exemple of utilisation : 
* cr�er objet 
* cr�er boite : besoin de deux point repr�sentant : le sommet devant en bas � gauche 
* et son oppos� celui au fond en haut � droite
* 
* cr�er un OctreeNode et inser�rer un par un les objets dedans 
* on pourra faire direct une m�thode d'insertion d'un tableau d'objet dans le octreeNode quand ca sera un peu plus concret
* 
	Object* obj1 = new Object(Vector(10, 10, 10), 10);
	Object* obj2 = new Object(Vector(100, 100, 100), 10);
	Object* obj3 = new Object(Vector(499, 100, 100), 10);
	Object* obj4 = new Object(Vector(200, 200, 200), 20);
	Object* obj5 = new Object(Vector(300, 300, 300), 10);
	Object* obj6 = new Object(Vector(1, 1, 1), 10);
	Object* obj7 = new Object(Vector(250, 250, 250), 10);

	BoundingBox boundingBox = BoundingBox(Vector(0, 0, 0), Vector(500, 500, 500));

	OctreeNode* octree = new OctreeNode(boundingBox);

	octree->Insert(obj1);
	octree->Insert(obj2);
	octree->Insert(obj3);
	octree->Insert(obj4);
	octree->Insert(obj5);
	octree->Insert(obj6);
	octree->Insert(obj7);

	octree->Display();

*/