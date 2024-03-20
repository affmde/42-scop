#include "Object.hpp"

Object::Object()
{
	this->totalFaces = 0;
}
Object::~Object() {}

void Object::setName(std::string name) { this->name = name; }
void Object::addVertices(std::vector<Vertex> vertices) { this->vertices = vertices; }
void Object::addVertex(Vertex vertex) { this->vertices.push_back(vertex); }
void Object::setMaterialName(std::string materialName) { this->materialName = materialName; }
void Object::increaseTotalFaces() { this->totalFaces++; }

std::string Object::getName() const { return this->name; }
std::vector<Vertex> &Object::getVertices() { return this->vertices; }
std::string Object::getMaterialName() const { return this->materialName; }
int Object::getTotalFaces() const { return this->totalFaces; }

void Object::addPositionIndex(int index) { this->verticePositionIndex.push_back(index); }
void Object::addTextureCoordIndex(int index) { this->verticeTextureCoordIndex.push_back(index); }
void Object::addNormalIndex(int index) { this->verticeNormalIndex.push_back(index); }

std::vector<int> &Object::getPositionIndices() { return this->verticePositionIndex; }
std::vector<int> &Object::getTextureCoordIndices() { return this->verticeTextureCoordIndex; }
std::vector<int> &Object::getNormalIndices() { return this->verticeNormalIndex; }