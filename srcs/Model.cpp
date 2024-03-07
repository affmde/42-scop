#include <iostream>

#include "Model.hpp"

Model::Model() {}

void Model::parse()
{
	this->parser.readFile("Models/andre.obj");
}

void Model::printVertices() const
{
	for(auto &vertice : this->vertices)
		std::cout << vertice << std::endl;
}