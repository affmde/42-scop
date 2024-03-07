#include "Parser.hpp"

#include <fstream>

Parser::Parser() {}

void Parser::readFile(std::string pathFile)
{
	std::ifstream file(pathFile);
	std::string line;
	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			std::cout << line << std::endl;
		}
		file.close();
	}
}