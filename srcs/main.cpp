#include <iostream>

#include "Parser.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		std::cout << "Not correct nuber of arguments" << std::endl;
		return 0;
	}
	Parser parser;
	parser.readFile("main.cpp");
	std::cout << "Hello World" << std::endl;
	return 0;
}