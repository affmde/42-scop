#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>

class Parser
{
public:
	Parser();
	~Parser() {}

	void readFile(std::string filePath);
};

#endif