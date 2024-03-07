#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>
#include <vector>

#include "Vertice.hpp"
#include "VerticeTexture.hpp"

class Parser
{
public:
	Parser();
	~Parser() {}

	void readFile(std::string filePath);
private:
	std::vector<std::string> vertexNormals;
	std::vector<std::string> vertexTexture;
	std::vector<std::string> vertices;
	std::vector<std::string> faces;

	std::vector<Vertice> parsedVertices;
	std::vector<Vertice> parsedVerticesNormal;
	std::vector<VerticeTexture> parsedVerticesTexture;

	void parseLine(std::string line);
	void parseVerticeLine(std::string &line);
	void parseVerticeNormalLine(std::string &line);
	void parseVerticeTextureLine(std::string &line);
	void parseFaceLine(std::string &line);
};

#endif