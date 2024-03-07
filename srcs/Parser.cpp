#include <fstream>
#include <iostream>

#include "Parser.hpp"
#include "Utils.hpp"

Parser::Parser() {}

void Parser::readFile(std::string pathFile)
{
	std::ifstream file(pathFile);
	std::string line;
	if(file.is_open())
	{
		while(std::getline(file, line))
			parseLine(line);
		file.close();
	}
	for(auto &line : this->vertices)
		this->parseVerticeLine(line);
	for(auto &line : this->vertexNormals)
		this->parseVerticeNormalLine(line);
	for(auto &line : this->vertexTexture)
		this->parseVerticeTextureLine(line);
	for(auto &v : this->parsedVerticesTexture)
		std::cout << v << std::endl;
}

void Parser::parseLine(std::string line)
{
	std::string indicator = line.substr(0, 2);
	if (indicator.compare("vt") == 0)
		this->vertexTexture.push_back(line);
	else if (indicator.compare("vn") == 0)
		this->vertexNormals.push_back(line);
	else if (indicator.compare("v ") == 0)
		this->vertices.push_back(line);
	else if (indicator.compare("f ") == 0)
		this->faces.push_back(line);
}

void Parser::parseVerticeLine(std::string &line)
{
	std::vector<std::string> words = str_split(line, " ");
	if (words.size() != 4)
		throw std::runtime_error("Invalid vertice found");

	float x = std::stof(words[1]);
	float y = std::stof(words[2]);
	float z = std::stof(words[3]);
	Vertice v(x, y, z);
	this->parsedVertices.push_back(v);
}
void Parser::parseVerticeNormalLine(std::string &line)
{
	std::vector<std::string> words = str_split(line, " ");
	if (words.size() != 4)
		throw std::runtime_error("Invalid vertice normal found");

	float x = std::stof(words[1]);
	float y = std::stof(words[2]);
	float z = std::stof(words[3]);
	Vertice vn(x, y, z);
	this->parsedVerticesNormal.push_back(vn);
}

void Parser::parseVerticeTextureLine(std::string &line)
{
	std::vector<std::string> words = str_split(line, " ");
	if (words.size() != 3)
		throw std::runtime_error("Invalid vertice texture");

	float x = std::stof(words[1]);
	float y = std::stof(words[2]);
	VerticeTexture vt(x, y);
	this->parsedVerticesTexture.push_back(vt);
}