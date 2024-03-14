#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <string>
#include <vector>

#include "Vector3f.hpp"
#include "Vector2f.hpp"

class Vertex
{
public:
	Vertex();
	Vertex(Vector3f position, Vector3f color, Vector2f texcoord, Vector3f normal);
	~Vertex();

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

	Vector3f position;
	Vector3f color;
	Vector2f texcoord;
	Vector3f normal;
};

#endif