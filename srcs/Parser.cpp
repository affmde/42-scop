#include <fstream>
#include <time.h>

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
			if (!verticesPosition.empty())
				vertices[i].position = verticesPosition[verticesPositionIndices[i] - 1];
			if (!verticesTextureCoord.empty())
				vertices[i].texcoord = verticesTextureCoord[verticesTexCoordIndices[i] - 1];
			if (!verticesNormalIndices.empty())
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
	for(auto &l : tempVertex)
	{
		indicesVec = str_split(l, "/");
		int counter = 0;
		for(auto &i : indicesVec)
		{
			if (counter == 0)
				verticesPositionIndices.push_back(std::stoi(i));
			else if (counter == 1)
				verticesTexCoordIndices.push_back(std::stoi(i));
			else if (counter == 2)
				verticesNormalIndices.push_back(std::stoi(i));
			++counter;
		}
	}
}