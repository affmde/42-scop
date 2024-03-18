#include <iostream>

#include "Scene.hpp"
#include "Checker.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <path_to_obj_file> <path_to_texture>" << std::endl;
		return 0;
	}
	try
	{
		Checker checker(argv[1]);
		checker.check();
		Scene scene(800, 600, "42-Scop", argv[1]);
		while(!scene.windowShouldClose())
		{
			scene.update();
			scene.render();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}