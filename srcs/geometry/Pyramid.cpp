#include "Pyramid.hpp"

Pyramid::Pyramid()
{
	Vertex testVertices[12];

	testVertices[0] = {Vector3f(0, 0.5f, 0),		Vector3f(1.f, 0, 0),	Vector2f(0.5f, 1.f),			Vector3f(0, 0, 1)};
	testVertices[1] = {Vector3f(-0.5f, -0.5f, 0.5f),	Vector3f(0, 1.f, 0),	Vector2f(0.f, 0.f),			Vector3f(0, 0, 1)};
	testVertices[2] = {Vector3f(0.5f, -0.5f, 0.5f),	Vector3f(0, 0, 1.f),	Vector2f(1.f, 0.f),			Vector3f(0, 0, 1)};

	testVertices[3] = {Vector3f(0, 0.5f, 0),		Vector3f(1.f, 1.f, 0),	Vector2f(0.5f, 1.f),			Vector3f(-1.f, 0, 0)};
	testVertices[4] = {Vector3f(-0.5f, -0.5f, -0.5f),	Vector3f(0, 0, 1.f),	Vector2f(0.f, 0.f),			Vector3f(-1.f, 0, 0)};
	testVertices[5] = {Vector3f(-0.5f, -0.5f, 0.5f),	Vector3f(0, 0, 1.f),	Vector2f(1.f, 0.f),			Vector3f(-1.f, 0, 0)};

	testVertices[6] = {Vector3f(0, 0.5f, 0),		Vector3f(1.f, 1.f, 0),	Vector2f(0.5f, 1.f),			Vector3f(0, 0, -1.f)};
	testVertices[7] = {Vector3f(0.5f, -0.5f, -0.5f),	Vector3f(0, 0, 1.f),	Vector2f(0.f, 0.f),			Vector3f(0, 0, -1.f)};
	testVertices[8] = {Vector3f(-0.5f, -0.5f, -0.5f),	Vector3f(0, 0, 1.f),	Vector2f(1.f, 0.f),			Vector3f(0, 0, -1.f)};

	testVertices[9] = {Vector3f(0, 0.5f, 0),		Vector3f(1.f, 1.f, 0),	Vector2f(0.5f, 1.f),			Vector3f(1.f, 0, 0)};
	testVertices[10] = {Vector3f(0.5f, -0.5f, 0.5f),	Vector3f(0, 0, 1.f),	Vector2f(1.f, 0.f),			Vector3f(1.f, 0, 0)};
	testVertices[11] = {Vector3f(0.5f, -0.5f, -0.5f),	Vector3f(0, 0, 1.f),	Vector2f(1.f, 0.f),			Vector3f(1.f, 0, 0)};

	unsigned int nbrOfVertices = sizeof(testVertices) / sizeof(Vertex);

	this->set(testVertices, nbrOfVertices, nullptr, 0);
}