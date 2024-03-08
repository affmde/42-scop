#ifndef MESH_HPP
# define MESH_HPP

#include <vector>

#include "Vertex.hpp"

class Mesh
{
public:
	Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices);
	~Mesh() {};

	void update();
	void render();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	void initVertexData(
		Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices);
	void initVAO();
	void initModelMatrices();
};

#endif