#include <iostream>
#include <MLX42/MLX42.h>

#include "Checker.hpp"
#include "Parser.hpp"
#include "Display.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Error: Not correct nuber of arguments" << std::endl;
		return 0;
	}
	try {
		Checker checker(argv[1], argv[2]);
		checker.check();
		Parser parser;
		parser.readFile(argv[1]);
		Display display;
		const std::vector<Vertex *> &vertices = parser.getVertices();
		display.init(400, 400, vertices);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 0;
	}
	
	
	return 0;
}