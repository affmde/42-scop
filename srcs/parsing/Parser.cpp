#include <fstream>
#include <time.h>
#include <iostream>
#include <limits.h>

#include "Parser.hpp"
#include "Utils.hpp"
#include "Vertex.hpp"
#include "Object.hpp"

Parser::Parser()
{
	std::srand(time(NULL));
}
Parser::~Parser() {}

std::unordered_map<std::string, Object*> Parser::loadObj(std::string pathFile)
{
	std::ifstream file(pathFile);
	std::string line;
	std::string prefix = "";
	Vector3f tempVec3;
	Vector2f tempVec2;

	std::string currentName = "";
	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;
			if (prefix == "#") {}
			else if(prefix == "mtllib")
			{
				std::string mtlPath;
				ss >> mtlPath;
				this->mtlLibs.push_back(mtlPath);
			}
			else if (prefix == "o")
			{
				std::string name;
				ss >> name;
				currentName = name;
				this->objects[currentName] = new Object();
				this->objects[currentName]->setName(name);
			}
			else if (prefix == "s") {}
			else if (prefix == "use_mtl" || prefix == "usemtl")
			{
				std::string materialName;
				ss >> materialName;
				objects[currentName]->setMaterialName(materialName);
			}
			else if (prefix == "v")
			{
				Vector3f vector = this->parseV_VN(ss);
				verticesPosition.push_back(vector);
			}
			else if (prefix == "vt")
			{
				Vector2f vector = this->parseVT(ss);
				verticesTextureCoord.push_back(vector);
			}
			else if (prefix == "vn")
			{
				Vector3f vector = this->parseV_VN(ss);
				verticesNormal.push_back(vector);
			}
			else if (prefix == "f")
			{
				objects[currentName]->increaseTotalFaces();
				parseFaceLine(ss, *this->objects[currentName]);
			}
			else {}
		}
		file.close();
		this->populateVertex();
	}
	else
		throw std::runtime_error("Error: Could not open file " + pathFile);
	return this->objects;
}

void Parser::populateVertex()
{
	for(auto &obj : this->objects)
	{
		obj.second->getVertices().resize(obj.second->getPositionIndices().size());
		for(unsigned int i = 0; i < obj.second->getPositionIndices().size(); i++)
		{
			Vertex vertex;
			if (!verticesPosition.empty() && obj.second->getPositionIndices()[i] != -1)
				vertex.position = verticesPosition[obj.second->getPositionIndices()[i] - 1];
			if (!verticesTextureCoord.empty() && obj.second->getTextureCoordIndices()[i] != -1)
				vertex.texcoord = verticesTextureCoord[obj.second->getTextureCoordIndices()[i] - 1];
			if (!verticesNormal.empty() && obj.second->getNormalIndices()[i] != -1)
				vertex.normal = verticesNormal[obj.second->getNormalIndices()[i] - 1];
			vertex.color = getRandomColor();
			obj.second->addVertex(vertex);
		}
	}
}

Vector3f Parser::parseV_VN(std::stringstream &ss)
{
	std::string line = ss.str();
	std::vector<std::string> tempVertex = str_split(line, " ");
	if (tempVertex.size() != 4)
		throw std::runtime_error("Error: Invalid vertex: " + line);
	Vector3f vec;
	try  {
		for(unsigned int i = 1; i < tempVertex.size(); i++)
			invalidVecValue(tempVertex[i]);
		vec.x = std::stof(tempVertex[1]);
		vec.y = std::stof(tempVertex[2]);
		vec.z = std::stof(tempVertex[3]);
	} catch(std::exception &e) {
		throw std::runtime_error("Error: Invalid vertex: " + line);
	}
	return vec;
}
Vector2f Parser::parseVT(std::stringstream &ss)
{
	std::string line = ss.str();
	std::vector<std::string> tempVertex = str_split(line, " ");
	if (tempVertex.size() != 3)
		throw std::runtime_error("Error: Invalid texture coordinate: " + line);
	Vector2f vec;
	try
	{
		for(unsigned int i = 1; i < tempVertex.size(); i++)
			invalidVecValue(tempVertex[i]);
		vec.x = std::stof(tempVertex[1]);
		vec.y = std::stof(tempVertex[2]);
	} catch(std::exception &e) {
		throw std::runtime_error("Error: Invalid texture coordinate: " + line);
	}
	return vec;
}

void Parser::invalidVecValue(std::string &val)
{
	this->checkForOverflow(val);
	for(unsigned int i = 0; i < val.size(); i++)
	{
		if (!isdigit(val[i]) && val[i] != '.' && val[i] != '-')
			throw std::runtime_error("Error: Invalid vertex: " + val);
		if ((val[i] == '-' && i != 0 ) || (val[i] == '+' && i != 0))
			throw std::runtime_error("Error: Invalid vertex: " + val);
	}
}

void Parser::parseFaceLine(std::stringstream &ss, Object &currentOject)
{
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
		populateIndices(indicesVec1, currentOject);
		populateIndices(indicesVec2, currentOject);
		populateIndices(indicesVec3, currentOject);
		vert2++;
		vert3++;
	}
}

void Parser::populateIndices(const std::vector<std::string> &vec, Object &currentObject)
{
	int counter = 0;
	for(auto &v : vec)
		{
			if (counter == 0)
				currentObject.addPositionIndex(std::stoi(v));
			else if (counter == 1)
			{
				if (!v.compare(""))
					currentObject.addTextureCoordIndex(-1);
				else
					currentObject.addTextureCoordIndex(std::stof(v));
			}
			else if (counter == 2)
			{
				if (!v.compare(""))
					currentObject.addNormalIndex(-1);
				else
					currentObject.addNormalIndex(std::stof(v));
			}
			++counter;
		}
}

void Parser::validateFace(std::vector<std::string> &v1, std::vector<std::string> &v2, std::vector<std::string> &v3)
{
	if (v1.size() > 3 || v2.size() > 3 || v3.size() > 3)
		throw std::runtime_error("Error: Invalid face");
	validateVertice(v1);
	validateVertice(v2);
	validateVertice(v3);
}
void Parser::validateVertice(std::vector<std::string> &v)
{
	unsigned int i = 0;
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

Object &Parser::getObjectByVertexId(int id)
{
	int commulativeFaces = 0;
	for(auto &obj : this->objects)
	{
		commulativeFaces += obj.second->getTotalFaces();
		if (id <= commulativeFaces)
			return *obj.second;
	}
	throw std::runtime_error("Error: Could not find object with id: " + std::to_string(id)
	+ " Comulative: " + std::to_string(commulativeFaces));
}

const std::vector<std::string> &Parser::getMtlLibs() const { return this->mtlLibs; }