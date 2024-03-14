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
		const unsigned int &numberOfIndices);
	Mesh(Primitive *primitive);
	~Mesh();

	Mesh(const Mesh &other);

	void update();
	void render(ShaderLoader *shader);
	void setPosition(Vector3f position);
	void setRotation(Vector3f rotation);
	void setScale(Vector3f scale);
	void move(Vector3f position);
	void rotate(Vector3f rotation);
	void zoom(Vector3f scale);

private:
	Vertex *vertexArray;
	unsigned int *indexArray;
	unsigned int numberOfVertices;
	unsigned int numberOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Mat4 modelMatrix;

	void initVAO();
	void updateUniformShader(ShaderLoader *shader);
	void updateModelMatrix();
};

#endif