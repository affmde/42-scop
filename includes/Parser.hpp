#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>
#include <vector>
#include <sstream>

#include "Vector3f.hpp"
#include "Vector2f.hpp"
#include "Vertex.hpp"

class Parser
{
public:
	Parser();
	~Parser();

	std::vector<Vertex> loadObj(std::string filePath);

	void printVertices() const;

private:
	std::vector<Vector3f> verticesPosition;
	std::vector<Vector2f> verticesTextureCoord;
	std::vector<Vector3f> verticesNormal;

	std::vector<int> verticesPositionIndices;
	std::vector<int> verticesTexCoordIndices;
	std::vector<int> verticesNormalIndices;

	std::vector<Vertex> vertices;

	std::stringstream ss;

	void parseFaceLine(std::stringstream &line);
};

#endif