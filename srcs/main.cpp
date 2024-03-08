// #include <iostream>
// #include <MLX42/MLX42.h>

// #include "Checker.hpp"
// #include "Parser.hpp"
// #include "Display.hpp"

// int main(int argc, char **argv)
// {
// 	if (argc != 3)
// 	{
// 		std::cout << "Error: Not correct nuber of arguments" << std::endl;
// 		return 0;
// 	}
// 	try {
// 		Checker checker(argv[1], argv[2]);
// 		checker.check();
// 		Parser parser;
// 		parser.readFile(argv[1]);
// 		Display display;
// 		const std::vector<Vertex *> &vertices = parser.getVertices();
// 		display.init(400, 400, vertices);
// 	} catch (std::exception &e) {
// 		std::cerr << "Error: " << e.what() << std::endl;
// 		return 0;
// 	}
	
	
// 	return 0;
// }

// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string>

void updateInput()
{
	GLFWwindow *window = glfwGetCurrentContext();
	if (!window)
		return;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void resizeWindow(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

bool loadShaders(GLuint &program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string line = "";
	std::string source = "";
	std::ifstream file;

	//Vertex

	//Shader
	file.open("srcs/shaders/vertex_core.glsl");
	if (file.is_open())
	{
		while(std::getline(file, line))
			source += line + "\n";
	}
	else
		std::cerr << "Error: Unable to open vertex_core.glsl" << std::endl;
	file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vertSource = source.c_str();
	glShaderSource(vertexShader, 1, &vertSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Error: Unable to compile vertex shader" << std::endl;
		std::cout << "Infolog: " << infoLog << std::endl;
	}

	line = "";
	source = "";

	//Fragment
	file.open("srcs/shaders/fragment_core.glsl");
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			source += line + "\n";
		}
	}
	else
	{
		loadSuccess = false;
		std::cerr << "Error: Unable to open fragment_core.glsl" << std::endl;
	}
	file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragSource = source.c_str();
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Error: Unable to compile fragment shader" << std::endl;
		std::cout << "Infolog: " << infoLog << std::endl;
		loadSuccess = false;
	}


	//Program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "Error: Unable to link program" << std::endl;
		std::cout << "Infolog: " << infoLog << std::endl;
		loadSuccess = false;
	}

	//Clean up
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return loadSuccess;
}

int main(void)
{
    if (!glfwInit())
	{
		std::cout << "Error: glfwInit failed" << std::endl;
		return -1;
	}
	int screenWidth = 800;
	int screenHeight = 600;
	// int frameBufferWidth = 0;
	// int frameBufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   FOR MACOS

	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "42-Scop", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create a window" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwSetFramebufferSizeCallback(window, resizeWindow);

	glfwMakeContextCurrent(window);

	// GLAD INITIALIZER
	if (!gladLoadGL())
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return 0;
	}

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//SHADER INIT
	GLuint coreProgram;
	if(!loadShaders(coreProgram))
	{
		glfwTerminate();
		return 0;
	}

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		updateInput();


		glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwSwapBuffers(window);
		glFlush();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	//glDeleteProgram(coreProgram);

    return 0;
}