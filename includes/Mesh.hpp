#ifndef MESH_HPP
# define MESH_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Vertex.hpp"
#include "ShaderLoader.hpp"
#include "Mat4.hpp"

class Mesh
{
public:
	Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices);
	~Mesh();

	void update();
	void render(ShaderLoader *shader);

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Mat4 modelMatrix;

	void initVertexData(
		Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices);
	void initVAO();
	void initModelMatrices();
	void updateUniformShader(ShaderLoader *shader);
};

#endif