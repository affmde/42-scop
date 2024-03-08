#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>
#include <vector>

#include "Vector2f.hpp"
#include "VerticeTexture.hpp"
#include "Vertex.hpp"

class Parser
{
public:
	Parser();
	~Parser();

	void readFile(std::string filePath);
	const std::vector<Vertex *> &getVertices() const;

	void printVertices() const;

private:
	std::vector<std::string> vertexNormals;
	std::vector<std::string> vertexTexture;
	std::vector<std::string> vertices;
	std::vector<std::string> faces;

	std::vector<Vector2f> parsedVertices;
	std::vector<Vector2f> parsedVerticesNormal;
	std::vector<VerticeTexture> parsedVerticesTexture;

	std::vector<Vertex *> parsedVertex;

	void parseLine(std::string line);
	void parseVerticeLine(std::string &line);
	void parseVerticeNormalLine(std::string &line);
	void parseVerticeTextureLine(std::string &line);
	void parseFaceLine(std::string &line);
};

#endif