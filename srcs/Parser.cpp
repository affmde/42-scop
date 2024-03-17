#include <fstream>
#include <time.h>
#include <iostream>
#include <limits.h>

#include "Parser.hpp"
#include "Utils.hpp"
#include "Vertex.hpp"

Parser::Parser() 
{
	std::srand(time(NULL));
}
Parser::~Parser() {}

std::vector<Vertex> Parser::loadObj(std::string pathFile)
{
	std::ifstream file(pathFile);
	std::string line;
	std::string prefix = "";
	Vector3f tempVec3;
	Vector2f tempVec2;

	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "#") {}
			else if (prefix == "o") {}
			else if (prefix == "s") {}
			else if (prefix == "use_mtl") {}
			else if (prefix == "v")
			{
				ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				verticesPosition.push_back(tempVec3);
			}
			else if (prefix == "vt")
			{
				ss >> tempVec2.x >> tempVec2.y;
				verticesTextureCoord.push_back(tempVec2);
			}
			else if (prefix == "vn")
			{
				ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				verticesNormal.push_back(tempVec3);
			}
			else if (prefix == "f")
			{
				parseFaceLine(ss);
			}
			else {}
		}
		
		file.close();
		vertices.resize(verticesPositionIndices.size(), Vertex());
		for(int i = 0; i < vertices.size(); i++)
		{
			if (!verticesPosition.empty() && verticesPositionIndices[i] != -1)
				vertices[i].position = verticesPosition[verticesPositionIndices[i] - 1];
			if (!verticesTextureCoord.empty() && verticesTexCoordIndices[i] != -1)
				vertices[i].texcoord = verticesTextureCoord[verticesTexCoordIndices[i] - 1];
			if (!verticesNormal.empty() && verticesNormalIndices[i] != -1)
				vertices[i].normal = verticesNormal[verticesNormalIndices[i] - 1];
			vertices[i].color = getRandomColor();
		}
	}
	else
		throw std::runtime_error("Error: Could not open file " + pathFile);
	return vertices;
}

void Parser::parseFaceLine(std::stringstream &ss)
{
	int temp;
	int counter = 0;
	std::string str(ss.str());
	std::vector<std::string> tempVertex = str_split(str, " ");
	tempVertex.erase(tempVertex.begin());
	std::vector<std::string> indicesVec;
	int vert1 = 0;
	int vert2 = 1;
	int vert3 = 2;
	int totalVerticesInFace = tempVertex.size();
	while(vert3 < totalVerticesInFace)
	{
		std::vector<std::string> indicesVec1 = str_split(tempVertex[vert1], "/");
		std::vector<std::string> indicesVec2 = str_split(tempVertex[vert2], "/");
		std::vector<std::string> indicesVec3 = str_split(tempVertex[vert3], "/");
		validateFace(indicesVec1, indicesVec2, indicesVec3);
		int counter = 0;

		for(auto &v : indicesVec1)
		{
			if (counter == 0)
				verticesPositionIndices.push_back(std::stof(v));
			else if (counter == 1)
			{
				if (!v.compare(""))
					verticesTexCoordIndices.push_back(-1);
				else
					verticesTexCoordIndices.push_back(std::stof(v));
			}
			else if (counter == 2)
			{
				if (!v.compare(""))
					verticesNormalIndices.push_back(-1);
				else
					verticesNormalIndices.push_back(std::stof(v));
			}
			++counter;
		}
		counter = 0;
		for(auto &v : indicesVec2)
		{
			if (counter == 0)
				verticesPositionIndices.push_back(std::stof(v));
			else if (counter == 1)
			{
				if (!v.compare(""))
					verticesTexCoordIndices.push_back(-1);
				else
					verticesTexCoordIndices.push_back(std::stof(v));
			}
			else if (counter == 2)
			{
				if (!v.compare(""))
					verticesNormalIndices.push_back(-1);
				else
					verticesNormalIndices.push_back(std::stof(v));
			}
			++counter;
		}
		counter = 0;
		for(auto &v : indicesVec3)
		{
			if (counter == 0)
				verticesPositionIndices.push_back(std::stof(v));
			else if (counter == 1)
			{
				if (!v.compare(""))
					verticesTexCoordIndices.push_back(-1);
				else
					verticesTexCoordIndices.push_back(std::stof(v));
			}
			else if (counter == 2)
			{
				if (!v.compare(""))
					verticesNormalIndices.push_back(-1);
				else
					verticesNormalIndices.push_back(std::stof(v));
			}
			++counter;
		}
		vert2++;
		vert3++;
	}
}


void Parser::validateFace(std::vector<std::string> &v1, std::vector<std::string> &v2, std::vector<std::string> &v3)
{
	if (v1.size() > 3 || v2.size() > 3 || v3.size() > 3)
	{
		for(auto &v : v1)
			std::cout << v << std::endl;
		for(auto &v : v2)
			std::cout << v << std::endl;
		for(auto &v : v3)
			std::cout << v << std::endl;
		throw std::runtime_error("Error: Invalid face");
	}
	validateVertice(v1);
	validateVertice(v2);
	validateVertice(v3);
}
void Parser::validateVertice(std::vector<std::string> &v)
{
	int i = 0;
	while(i < v.size())
	{
		if (i == 0)
			validateVerticeData(v[i], this->verticesPosition.size());
		else if (i == 1)
			validateVerticeData(v[i], this->verticesTextureCoord.size());
		else if (i == 2)
			validateVerticeData(v[i], this->verticesNormal.size());
		i++;
	}
}
void Parser::validateVerticeData(std::string &data, size_t vectorSize)
{
	for(auto &c : data)
	{
		if (!isdigit(c))
			throw std::runtime_error("Error: Invalid face: " + data);
		this->checkForOverflow(data);
		this->checkInvalidIndex(data, vectorSize);
	}
}
void Parser::checkForOverflow(std::string &line)
{
	try {
		long long number = std::stoll(line);
		if (number > INT_MAX || number < INT_MIN)
			throw std::runtime_error("Error: Overflow: " + line);
	} catch (std::exception &e) {
		throw std::runtime_error("Error: Overflow: " + line);
	}
}
void Parser::checkInvalidIndex(std::string &line, int size)
{
	try {
		long long number = std::stoll(line);
		if (number > size || number < 0)
			throw std::runtime_error("Error: Invalid index: " + line);
	} catch (std::exception &e) {
		throw std::runtime_error(e.what());
	}
}