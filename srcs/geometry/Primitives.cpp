#include "Primitives.hpp"

Primitive::Primitive() {}
Primitive::~Primitive() {}

void Primitive::set(const Vertex *verices, const unsigned int numberOfVertices, const unsigned int *indices, const unsigned int numberOfIndices)
{
	this->vertices.clear();
	this->indices.clear();

	for (unsigned int i = 0; i < numberOfVertices; i++)
		this->vertices.push_back(verices[i]);

	for (unsigned int i = 0; i < numberOfIndices; i++)
		this->indices.push_back(indices[i]);
}

Vertex *Primitive::getVertices() { return this->vertices.data(); }
unsigned int *Primitive::getIndices() { return this->indices.data(); }
unsigned int Primitive::getNumberOfVertices() const { return this->vertices.size(); }
unsigned int Primitive::getNumberOfIndices() const { return this->indices.size(); }