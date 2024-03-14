#include "Mesh.hpp"
#include "Utils.hpp"

Mesh::Mesh(Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices) : modelMatrix(1.f)
{
	this->scale = Vector3f(1.f);
	this->initVAO(vertexArray, numberOfVertices, indexArray, numberOfIndices);
}

Mesh::Mesh(Primitive *primitive) : modelMatrix(1.f)
{
	this->scale = Vector3f(1.f);
	this->initVAO(primitive);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	if (this->numberOfIndices > 0)
		glDeleteBuffers(1, &this->EBO);
}

void Mesh::initVAO(Primitive *primitive)
{
	this->numberOfVertices = primitive->getNumberOfVertices();
	this->numberOfIndices = primitive->getNumberOfIndices();

	//VAO -> VERTEX ARRAY OBJECT
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//VBO -> Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, primitive->getNumberOfVertices() * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW);

	//EBO -> Element Buffer Object
	if (this->numberOfIndices > 0)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, primitive->getNumberOfIndices() * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);
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

void Mesh::initVAO(
	Vertex *vertexArray,
		const unsigned int &numberOfVertices,
		unsigned int* indexArray,
		const unsigned int &numberOfIndices
)
{
	this->numberOfVertices = numberOfVertices;
	this->numberOfIndices = numberOfIndices;

	//VAO -> VERTEX ARRAY OBJECT
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//VBO -> Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->numberOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

	//EBO -> Element Buffer Object
	if (this->numberOfIndices > 0)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numberOfIndices* sizeof(GLuint), indexArray, GL_STATIC_DRAW);
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

void Mesh::setPosition(Vector3f position) { this->position = position; }
void Mesh::setRotation(Vector3f rotation) { this->rotation = rotation; }
void Mesh::setScale(Vector3f scale) { this->scale = scale; }
void Mesh::move(Vector3f position) { this->position += position; }
void Mesh::rotate(Vector3f rotation) { this->rotation += rotation; }
void Mesh::zoom(Vector3f scale) { this->scale += scale; }
