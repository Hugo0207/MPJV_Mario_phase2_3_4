#include "OctreeNode.h"

BoundingBox::BoundingBox(const Vector& min, const Vector& max)
{
	m_min = min;
	m_max = max;
}
bool BoundingBox::IsContainingObject(Sphere* object)
{
	const Vector& center = object->center;
	float radius = object->radius;
	return (center.x + radius >= m_min.x && center.x - radius <= m_max.x) &&
		(center.y + radius >= m_min.y && center.y - radius <= m_max.y) &&
		(center.z + radius >= m_min.z && center.z - radius <= m_max.z);
}

//draw the edge of the boudingBox
void BoundingBox::draw()
{
	//define all the vertices of the box
	Vector vertices[8] = {
	m_min,
	{m_max.x, m_min.y, m_min.z},
	{m_max.x, m_max.y, m_min.z},
	{m_min.x, m_max.y, m_min.z},
	{m_min.x, m_min.y, m_max.z},
	{m_max.x, m_min.y, m_max.z},
	m_max,
	{m_min.x, m_max.y, m_max.z}
	};

	//define the edges btwn vertices
	int edges[12][2] = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0},
		{4, 5}, {5, 6}, {6, 7}, {7, 4},
		{0, 4}, {1, 5}, {2, 6}, {3, 7} 
	};

	ofSetColor(0, 0, 0);
	ofSetLineWidth(1);

	//draw the edges
	for (auto& edge : edges) ofDrawLine(vertices[edge[0]].toVec3(), vertices[edge[1]].toVec3());
}


OctreeNode::OctreeNode()
{
	BoundingBox nullBounds(Vector(0, 0, 0), Vector(0, 0, 0));
	m_bounds = nullBounds;

	for (int i = 0; i < 8; i++) children[i] = nullptr;
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
	children[2] = new OctreeNode(BoundingBox(Vector(min.x, mid.y, min.z), Vector(mid.x, max.y, mid.z)));
	children[3] = new OctreeNode(BoundingBox(Vector(mid.x, mid.y, min.z), Vector(max.x, max.y, mid.z)));
	children[5] = new OctreeNode(BoundingBox(Vector(min.x, min.y, mid.z), Vector(mid.x, mid.y, max.z)));
	children[4] = new OctreeNode(BoundingBox(Vector(mid.x, min.y, mid.z), Vector(max.x, mid.y, max.z)));
	children[6] = new OctreeNode(BoundingBox(Vector(min.x, mid.y, mid.z), Vector(mid.x, max.y, max.z)));
	children[7] = new OctreeNode(BoundingBox(mid, max));
}
void OctreeNode::Insert(Sphere* obj)
{
	//if there are children, distribute objects in children
	if (children[0] != nullptr)
	{
		Distribute(obj);
		return;
	}
	//else push back in the object vector 
	m_objects.push_back(obj);
	obj->currentOctree = this;
	// if size of the vector taller than max objects
	// split octreenode in children and distribute objects in them
	if (m_objects.size() > MAX_OBJECTS)
	{
		Split();
		for (Sphere* object : m_objects)
		{
			Distribute(object);
		}
		m_objects.clear();
	}
}
void OctreeNode::Distribute(Sphere* obj)
{
	for (int i = 0; i < 8; i++) {
		if (children[i]->m_bounds.IsContainingObject(obj)) {
			children[i]->Insert(obj);
		}
	}
}


void OctreeNode::Display(int depth) {
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	// depth of the node
	std::string indent(depth * 2, ' ');
	// show informations of the current node
	std::cout << indent << "Node at depth " << depth << "\n";
	std::cout << indent << "  Bounding Box: [(" << m_bounds.m_min.x << ", " << m_bounds.m_min.y << ", " << m_bounds.m_min.z << ")"
		<< " -> (" << m_bounds.m_max.x << ", " << m_bounds.m_max.y << ", " << m_bounds.m_max.z << ")]\n";
	std::cout << indent << "  Objects: " << m_objects.size() << "\n";

	//show center of the objects
	for (Sphere* object : m_objects)
	{
		std::cout << indent << "    [" << object->center.x << ", " << object->center.y << ", " << object->center.z << "]\n";
	}
	// show child if exists
	if (children[0] != nullptr) {
		for (int i = 0; i < 8; ++i) {
			std::cout << "\n" << indent << "  Child " << i << ":\n";
			//call the display of the child
			children[i]->Display(depth + 1);
		}
	}
}
bool BoundingBox::intersectsPlane(const Vector& planePoint, const Vector& planeNormal) const {
	Vector closestPoint = m_min;
	if (planeNormal.x > 0) closestPoint.x = m_max.x;
	if (planeNormal.y > 0) closestPoint.y = m_max.y;
	if (planeNormal.z > 0) closestPoint.z = m_max.z;
	float distance = planeNormal.dotProduct(closestPoint - planePoint);
	return distance <= 0.0f;
}

void OctreeNode::draw() {
	m_bounds.draw();

	for (int i = 0; i < 8; ++i) {
		if (children[i]) {
			children[i]->draw();
		}
	}
}
