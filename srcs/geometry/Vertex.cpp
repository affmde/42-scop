#include "Vertex.hpp"

Vertex::Vertex() {}
Vertex::Vertex(Vector3f position, Vector3f color, Vector2f texcoord, Vector3f normal)
{
	this->position = position;
	this->color = color;
	this->texcoord = texcoord;
	this->normal = normal;

}
Vertex::~Vertex() {}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
	return os << vertex.position << " | " << vertex.texcoord << " | " << vertex.texcoord << " | " << vertex.color << std::endl;
}