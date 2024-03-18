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

	void populateVertex();
	void populateIndices(const std::vector<std::string> &vec);

	Vector3f parseV_VN(std::stringstream &ss);
	Vector2f parseVT(std::stringstream &ss);
	void invalidVecValue(std::string &val);
	void parseFaceLine(std::stringstream &line);
	void validateVerticeData(std::string &data, size_t vectorSize);
	void validateFace(std::vector<std::string> &v1, std::vector<std::string> &v2, std::vector<std::string> &v3);
	void checkForOverflow(std::string &line);
	void checkInvalidIndex(std::string &line, int size);
	void validateVertice(std::vector<std::string> &v);
};

#endif