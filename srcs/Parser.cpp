#include <fstream>
#include <iostream>

#include "Parser.hpp"
#include "Utils.hpp"
#include "Face.hpp"

Parser::Parser() {}
Parser::~Parser() 
{
	for(auto &f : this->parsedFaces)
		delete f;
	this->parsedFaces.clear();
}

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
	for(auto &line : this->faces)
		this->parseFaceLine(line);
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

void Parser::parseFaceLine(std::string &line)
{
	std::vector<std::string> points = str_split(line, " ");
	
	points.erase(points.begin());
	std::vector<unsigned int> v, vt, vn;

	for(unsigned int i = 0; i < points.size(); i++)
	{
		std::vector<std::string> elements = str_split(points[i], "/");
		for(unsigned int j = 0; j < elements.size(); j++)
		{
			int index = j % 3;
			if (index == 0)
				v.push_back(std::stoi(elements[j]));
			else if (index == 1)
				vt.push_back(std::stoi(elements[j]));
			else
				vn.push_back(std::stoi(elements[j]));
		}
	}
	Face *face = new Face();
	for(auto &vertice : v)
		face->addV(Vertice(this->parsedVertices[vertice - 1]));
	for(auto &vnormal : vn)
		face->addVN(Vertice(this->parsedVerticesNormal[vnormal - 1]));
	for(auto &vtexture : vt)
		face->addVT(VerticeTexture(this->parsedVerticesTexture[vtexture - 1]));
	this->parsedFaces.push_back(face);
}

const std::vector<Face *> &Parser::getFaces() const { return this->parsedFaces; }
void Parser::printFaces() const
{
	for(auto &f : this->parsedFaces)
		std::cout << *f << std::endl;
}