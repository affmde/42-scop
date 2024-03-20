#ifndef OBJECT_HPP
# define OBJECT_HPP

#include <vector>

#include "Vertex.hpp"

class Object
{
public:
	Object();
	~Object();

	void setName(std::string name);
	void addVertices(std::vector<Vertex> vertices);
	void addVertex(Vertex vertex);
	void setMaterialName(std::string materialName);
	void increaseTotalFaces();

	std::string getName() const;
	std::vector<Vertex> &getVertices();
	std::string getMaterialName() const;
	int getTotalFaces() const;

	void addPositionIndex(int index);
	void addTextureCoordIndex(int index);
	void addNormalIndex(int index);

	std::vector<int> &getPositionIndices();
	std::vector<int> &getTextureCoordIndices();
	std::vector<int> &getNormalIndices();
private:
	std::string name;
	std::vector<Vertex> vertices;
	std::string materialName;
	int totalFaces;

	std::vector<int> verticePositionIndex;
	std::vector<int> verticeTextureCoordIndex;
	std::vector<int> verticeNormalIndex;
};


#endif