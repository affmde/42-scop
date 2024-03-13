#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Vertex.hpp"
#include "ShaderLoader.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Triangle.hpp"
#include "Quad.hpp"
#include "Scene.hpp"

#define STB_IMAGE_IMPLEMENTATION
 #include "stb_images/stb_image.h"
 #define STB_IMAGE_WRITE_IMPLEMENTATION
 #include "stb_images/stb_image_write.h"

void updateInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// void resizeWindow(GLFWwindow *window, int width, int heigth)
// {
// 	(void)window;
// 	glViewport(0, 0, width, heigth);
// }

void handleInput(GLFWwindow *window, Mesh &mesh)
{
	
}

int main(void)
{
	Scene scene(800, 600, "42-Scop");
	while(!scene.windowShouldClose())
	{
		scene.update();
		scene.render();
	}
	return 0;
}