#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

#include "Vector3f.hpp"
#include "Vector2f.hpp"
#include "Vertex.hpp"
#include "Object.hpp"

class Parser
{
public:
	Parser();
	~Parser();

	std::unordered_map<std::string, Object*> loadObj(std::string filePath);
	const std::vector<std::string> &getMtlLibs() const;

	void printVertices() const;

private:

	std::unordered_map<std::string, Object*> objects;
	std::vector<std::string> mtlLibs;

	std::vector<Vector3f> verticesPosition;
	std::vector<Vector2f> verticesTextureCoord;
	std::vector<Vector3f> verticesNormal;

	std::vector<int> verticesPositionIndices;
	std::vector<int> verticesTexCoordIndices;
	std::vector<int> verticesNormalIndices;

	std::vector<Vertex> vertices;

	std::stringstream ss;

	void populateVertex();
	void populateIndices(const std::vector<std::string> &vec, Object &currentObject);

	Vector3f parseV_VN(std::stringstream &ss);
	Vector2f parseVT(std::stringstream &ss);
	void invalidVecValue(std::string &val);
	void parseFaceLine(std::stringstream &line, Object &currentObject);
	void validateVerticeData(std::string &data, size_t vectorSize);
	void validateFace(std::vector<std::string> &v1, std::vector<std::string> &v2, std::vector<std::string> &v3);
	void checkForOverflow(std::string &line);
	void checkInvalidIndex(std::string &line, int size);
	void validateVertice(std::vector<std::string> &v);

	Object &getObjectByVertexId(int id);
};

#endif