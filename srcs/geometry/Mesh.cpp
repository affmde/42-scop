#include "Mesh.hpp"

Mesh::Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices)
{
	this->initVertexData(vertexArray, numberOfVertices, indexArray, numberOfIndices);
	this->initVAO();
	this->initModelMatrices();
}

void Mesh::initVertexData(
		Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices)
{
	for(size_t i = 0; i < numberOfVertices; i++)
		this->vertices.push_back(vertexArray[i]);
	for(size_t i = 0; i < numberOfIndices; i++)
		this->indices.push_back(indexArray[i]);
}