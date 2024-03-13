#include "Mesh.hpp"
#include "Utils.hpp"

Mesh::Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices) : modelMatrix(1.f)
{
	this->scale = Vector3f(1.f);
	this->initVertexData(vertexArray, numberOfVertices, indexArray, numberOfIndices);
	this->initVAO();
	this->initModelMatrices();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
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

void Mesh::initVAO()
{
	//VAO -> VERTEX ARRAY OBJECT
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//VBO -> Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

	//EBO -> Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);

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

void Mesh::initModelMatrices()
{
	Mat4 tr = this->modelMatrix.translate(this->position);
	Mat4 rx = this->modelMatrix.rotate(toRadians(this->rotation.x), Vector3f(1.0f, 0.0f, 0.0f));
	Mat4 ry = this->modelMatrix.rotate(toRadians(this->rotation.y), Vector3f(0.0f, 1.0f, 0.0f));
	Mat4 rz = this->modelMatrix.rotate(toRadians(this->rotation.z), Vector3f(0.0f, 0.0f, 1.0f));
	Mat4 sc = this->modelMatrix.scale(this->scale);
}

void Mesh::updateUniformShader(ShaderLoader *shader)
{
	shader->setMat4(this->modelMatrix, "model");
}

void Mesh::render(ShaderLoader *shader)
{
	this->updateUniformShader(shader);
	shader->use();
	glBindVertexArray(this->VAO);

	if (this->indices.empty())
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	else
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}