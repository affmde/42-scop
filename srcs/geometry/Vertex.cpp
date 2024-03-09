#include "Vertex.hpp"

Vertex::Vertex() {}
Vertex::~Vertex() {}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
	return os << vertex.position << " | " << vertex.color << " | " << vertex.texcoord << std::endl;
}