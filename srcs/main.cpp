#include <iostream>

#include "Checker.hpp"

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
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 0;
	}
	
	return 0;
}