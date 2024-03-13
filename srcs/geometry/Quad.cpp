#include "Quad.hpp"

Quad::Quad()
{
	Vertex testVertices[4];

	testVertices[0].position = Vector3f(-0.5f, 0.5f, 0.0f);
	testVertices[1].position = Vector3f(-0.5f, -0.5f, 0.0f);
	testVertices[2].position = Vector3f(0.5f, -0.5f, 0.0f);
	testVertices[3].position = Vector3f(0.5f, 0.5f, 0.0f);

	testVertices[0].color = Vector3f(1.0f, 0.0f, 0.0f);
	testVertices[1].color = Vector3f(0.0f, 1.0f, 0.0f);
	testVertices[2].color = Vector3f(0.0f, 0.0f, 1.0f);
	testVertices[3].color = Vector3f(1.0f, 1.0f, 0.0f);

	testVertices[0].texcoord = Vector2f(0.0f, 1.0f);
	testVertices[1].texcoord = Vector2f(0.0f, 0.0f);
	testVertices[2].texcoord = Vector2f(1.0f, 0.0f);
	testVertices[3].texcoord = Vector2f(1.0f, 1.0f);

	testVertices[0].normal = Vector3f(0.0f, 0.0f, 1.0f);
	testVertices[1].normal = Vector3f(0.0f, 0.0f, 1.0f);
	testVertices[2].normal = Vector3f(0.0f, 0.0f, 1.0f);
	testVertices[3].normal = Vector3f(0.0f, 0.0f, 1.0f);

	unsigned int nbrOfVertices = sizeof(testVertices) / sizeof(Vertex);
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3};
	unsigned int nbrOfIndices = sizeof(indices) / sizeof(unsigned int);

	this->set(testVertices, nbrOfVertices, indices, nbrOfIndices);
}