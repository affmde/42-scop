#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>

#include "Scene.hpp"
#include "Parser.hpp"

#define STB_IMAGE_IMPLEMENTATION
 #include "stb_images/stb_image.h"
 #define STB_IMAGE_WRITE_IMPLEMENTATION
 #include "stb_images/stb_image_write.h"

int main(void)
{
	Parser parser;
	try
	{
		std::vector<Vertex> vertices = parser.loadObj("Models/andre.obj");
		Scene scene(800, 600, "42-Scop", vertices);
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