#ifndef PRIMITIVES_HPP
# define PRIMITIVES_HPP

#include <vector>

#include "Vertex.hpp"

class Primitive
{
public:
	Primitive();
	virtual ~Primitive();

	void set(const Vertex *verices, const unsigned int numberOfVertices, const unsigned int *indices, const unsigned int numberOfIndices);
	Vertex *getVertices();
	unsigned int *getIndices();
	const unsigned int getNumberOfVertices() const;
	const unsigned int getNumberOfIndices() const;


private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

#endif