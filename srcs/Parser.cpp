#include <fstream>
#include <iostream>

#include "Parser.hpp"
#include "Utils.hpp"
#include "Vertex.hpp"

Parser::Parser() {}
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
		// std::cout << "VerticesPositionSize: " << verticesPosition.size() << std::endl;
		// std::cout << "VerticesTextureCoordSize: " << verticesTextureCoord.size() << std::endl;
		// std::cout << "VerticesNormalSize: " << verticesNormal.size() << std::endl;
		// std::cout << "VerticesPositionIndicesSize: " << verticesPositionIndices.size() << std::endl;
		// std::cout << "VerticesTexCoordIndicesSize: " << verticesTexCoordIndices.size() << std::endl;
		// std::cout << "VerticesNormalIndicesSize: " << verticesNormalIndices.size() << std::endl;
		for(int i = 0; i < vertices.size(); i++)
		{
			if (!verticesPosition.empty())
				vertices[i].position = verticesPosition[verticesPositionIndices[i] - 1];
			if (!verticesTextureCoord.empty())
				vertices[i].texcoord = verticesTextureCoord[verticesTexCoordIndices[i] - 1];
			if (!verticesNormalIndices.empty())
				vertices[i].normal = verticesNormal[verticesNormalIndices[i] - 1];
			vertices[i].color = Vector3f(1.f);
		}
	}
	return vertices;
}

void Parser::parseFaceLine(std::stringstream &ss)
{
	int temp;
	int counter = 0;

	while(ss >> temp)
	{
		if (counter == 0)
			verticesPositionIndices.push_back(temp);
		else if (counter == 1)
			verticesTexCoordIndices.push_back(temp);
		else if (counter == 2)
			verticesNormalIndices.push_back(temp);
		if (ss.peek() == '/')
		{
			++counter;
			ss.ignore(1, '/');
		}
		else if(ss.peek() == ' ')
		{
			++counter;
			ss.ignore(1, ' ');
		}
		if (counter > 2)
			counter = 0;
	}
}