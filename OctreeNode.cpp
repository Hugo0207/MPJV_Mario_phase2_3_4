#include "OctreeNode.h"

Object::Object(Vector center, float radius) : center(center), radius(radius) {}

BoundingBox::BoundingBox(const Vector& min, const Vector& max)
{
	m_min = min; 
	m_max = max;
}

bool BoundingBox::IsContainingObject(Object* object)
{
	const Vector& center = object->center;
	float radius = object->radius;

	return (center.x + radius >= m_min.x && center.x - radius <= m_max.x) &&
		(center.y + radius >= m_min.y && center.y - radius <= m_max.y) &&
		(center.z + radius >= m_min.z && center.z - radius <= m_max.z);
}


OctreeNode::OctreeNode(const BoundingBox& bounds)
{
	m_bounds = bounds;
	
	for (int i = 0; i < 8; i++) children[i] = nullptr;
	
}

void OctreeNode::Split()
{
	Vector mid = (m_bounds.m_min + m_bounds.m_max) / 2.0f;
	Vector min = m_bounds.m_min;
	Vector max = m_bounds.m_max;

	//creating all the 8 combinaison of the node child
	children[0] = new OctreeNode(BoundingBox(min, mid));
	children[1] = new OctreeNode(BoundingBox(Vector(mid.x, min.y, min.z), Vector(max.x, mid.y, mid.z)));
	children[2] = new OctreeNode(BoundingBox(Vector(min.x,  mid.y, min.z), Vector(mid.x, max.y, mid.z)));
	children[3] = new OctreeNode(BoundingBox(Vector(mid.x, mid.y, min.z), Vector(max.x, max.y, mid.z)));
	children[5] = new OctreeNode(BoundingBox(Vector(min.x, min.y, mid.z), Vector(mid.x, mid.y, max.z)));
	children[4] = new OctreeNode(BoundingBox(Vector(mid.x, min.y, mid.z), Vector(max.x, mid.y, max.z)));
	children[6] = new OctreeNode(BoundingBox(Vector(min.x, mid.y, mid.z), Vector(mid.x, max.y, max.z)));
	children[7] = new OctreeNode(BoundingBox(mid, max));

}

void OctreeNode::Insert(Object* obj)
{
	//if there is children, distribute objecte in childrens
	if (children[0] != nullptr)
	{
		Distribute(obj);
		return;
	}

	//else push back in the object vector 
	m_objects.push_back(obj);

	// if size of the vector taller thant max objects
	// split octreenode in children and distribute objects in them
	if (m_objects.size() > MAX_OBJECTS)
	{
		Split();
		for (Object* object : m_objects) Distribute(object);

		m_objects.clear();
	}
}

void OctreeNode::Distribute(Object* obj)
{
	for (int i = 0; i < 8; i++){
		if (children[i]->m_bounds.IsContainingObject(obj)) {
			children[i]->Insert(obj);
		}
	}
}


void OctreeNode::Display(int depth) {
	// depth of the node
	std::string indent(depth * 2, ' ');

	// show informations of the current node
	std::cout << indent << "Node at depth " << depth << "\n";
	std::cout << indent << "  Bounding Box: [(" << m_bounds.m_min.x << ", " << m_bounds.m_min.y << ", " << m_bounds.m_min.z << ")"
		<< " -> (" << m_bounds.m_max.x << ", " << m_bounds.m_max.y << ", " << m_bounds.m_max.z << ")]\n";
	std::cout << indent << "  Objects: " << m_objects.size() << "\n";
	
	//show center of the objects
	for (Object* object : m_objects)
	{
		std::cout << indent << "    [" << object->center.x <<", "<< object->center.y <<", "<< object->center.z << "]\n";
	}

	// show child if exists
	if (children[0] != nullptr) {
		for (int i = 0; i < 8; ++i) {
			std::cout << "\n"<< indent << "  Child " << i << ":\n";

			//call the display of the child
			children[i]->Display(depth + 1);
		}
	}
}