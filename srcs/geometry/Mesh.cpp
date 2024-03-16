#include "Mesh.hpp"
#include "Utils.hpp"

#include <iostream>

Mesh::Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices,
		Vector3f origin) : modelMatrix(1.f)
{
	this->origin = origin;
	this->numberOfVertices = numberOfVertices;
	this->numberOfIndices = numberOfIndices;
	this->vertexArray = new Vertex[this->numberOfVertices];
	for(int i = 0; i < this->numberOfVertices; i++)
		this->vertexArray[i] = vertexArray[i];
	this->indexArray = new unsigned int[this->numberOfIndices];
	for(int i = 0; i < this->numberOfIndices; i++)
		this->indexArray[i] = indexArray[i];
	this->scale = Vector3f(1.f);
	this->initVAO();
	this->updateModelMatrix();
}

Mesh::Mesh(Primitive *primitive, Vector3f origin) : modelMatrix(1.f)
{
	this->origin = origin;
	this->numberOfVertices = primitive->getNumberOfVertices();
	this->numberOfIndices = primitive->getNumberOfIndices();
	this->vertexArray = new Vertex[this->numberOfVertices];
	for(int i = 0; i < this->numberOfVertices; i++)
		this->vertexArray[i] = primitive->getVertices()[i];
	this->indexArray = new unsigned int[this->numberOfIndices];
	for(int i = 0; i < this->numberOfIndices; i++)
		this->indexArray[i] = primitive->getIndices()[i];

	this->scale = Vector3f(1.f);
	this->initVAO();
	this->updateModelMatrix();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	if (this->numberOfIndices > 0)
		glDeleteBuffers(1, &this->EBO);

	delete[] this->vertexArray;
	delete[] this->indexArray;
}

Mesh::Mesh(const Mesh &other) : modelMatrix(1.f)
{
	this->origin = other.origin;
	this->numberOfVertices = other.numberOfVertices;
	this->numberOfIndices = other.numberOfIndices;
	this->vertexArray = new Vertex[this->numberOfVertices];
	for(int i = 0; i < this->numberOfVertices; i++)
		this->vertexArray[i] = other.vertexArray[i];
	this->indexArray = new unsigned int[this->numberOfIndices];
	for(int i = 0; i < this->numberOfIndices; i++)
		this->indexArray[i] = other.indexArray[i];
	this->scale = Vector3f(1.f);
	this->initVAO();
	this->updateModelMatrix();
}

void Mesh::initVAO()
{
	//VAO -> VERTEX ARRAY OBJECT
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//VBO -> Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->numberOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

	//EBO -> Element Buffer Object
	if (this->numberOfIndices > 0)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numberOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
	}

	Vertex v;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Mesh::updateUniformShader(ShaderLoader *shader)
{
	shader->setMat4(this->modelMatrix, "model");
}

void Mesh::render(ShaderLoader *shader)
{
	this->updateModelMatrix();
	this->updateUniformShader(shader);
	shader->use();
	glBindVertexArray(this->VAO);

	if (this->numberOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->numberOfVertices);
	else
		glDrawElements(GL_TRIANGLES, this->numberOfIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::updateModelMatrix()
{
	this->modelMatrix.reset();
	Mat4 tr = this->modelMatrix.translate(this->position);
	Mat4 rx = this->modelMatrix.rotate(toRadians(this->rotation.x), Vector3f(1.0f, 0.0f, 0.0f));
	Mat4 ry = this->modelMatrix.rotate(toRadians(this->rotation.y), Vector3f(0.0f, 1.0f, 0.0f));
	Mat4 rz = this->modelMatrix.rotate(toRadians(this->rotation.z), Vector3f(0.0f, 0.0f, 1.0f));
	Mat4 sc = this->modelMatrix.scale(this->scale);

	this->modelMatrix *= tr;
	this->modelMatrix *= rx;
	this->modelMatrix *= ry;
	this->modelMatrix *= rz;
	this->modelMatrix *= sc;
}

void Mesh::setPosition(const Vector3f position) { this->position = position; }
void Mesh::setRotation(const Vector3f rotation) { this->rotation = rotation; }
void Mesh::setScale(const Vector3f scale) { this->scale = scale; }
void Mesh::setOrigin(const Vector3f origin) { this->origin = origin; }
void Mesh::move(const Vector3f position) { this->position += position; }
void Mesh::rotate(const Vector3f rotation) { this->rotation += rotation; }
void Mesh::zoom(const Vector3f scale) { this->scale += scale; }
