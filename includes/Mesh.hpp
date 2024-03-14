#ifndef MESH_HPP
# define MESH_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Vertex.hpp"
#include "ShaderLoader.hpp"
#include "Mat4.hpp"
#include "Primitives.hpp"

class Mesh
{
public:
	Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices,
		Vector3f origin = Vector3f(0.f));
	Mesh(Primitive *primitive, Vector3f origin = Vector3f(0.f));
	~Mesh();

	Mesh(const Mesh &other);

	void update();
	void render(ShaderLoader *shader);
	void setPosition(const Vector3f position);
	void setRotation(const Vector3f rotation);
	void setScale(const Vector3f scale);
	void setOrigin(const Vector3f origin);
	void move(const Vector3f position);
	void rotate(const Vector3f rotation);
	void zoom(const Vector3f scale);

private:
	Vertex *vertexArray;
	unsigned int *indexArray;
	unsigned int numberOfVertices;
	unsigned int numberOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Vector3f origin;
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Mat4 modelMatrix;

	void initVAO();
	void updateUniformShader(ShaderLoader *shader);
	void updateModelMatrix();
};

#endif