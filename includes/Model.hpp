#ifndef MODEL_HPP
# define MODEL_HPP

#include <vector>

#include "Vertice.hpp"
#include "Parser.hpp"

class Model
{
public:
	Model();
	~Model(){}

	void parse();
	void printVertices() const;

private:
	Parser parser;
	std::vector<Vertice> vertices;
};

#endif