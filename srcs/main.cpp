#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Vertex.hpp"
#include "ShaderLoader.hpp"

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

int main(void)
{
    if (!glfwInit())
	{
		std::cout << "Error: glfwInit failed" << std::endl;
		return -1;
	}
	int screenWidth = 800;
	int screenHeight = 600;

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
	ShaderLoader shadeLoader("srcs/shaders/vertex_core.glsl", "srcs/shaders/fragment_core.glsl");
	GLuint coreProgram;
	if(!shadeLoader.loadShaders(coreProgram))
	{
		glfwTerminate();
		return 0;
	}


	/*
	FOR EXEMPLE PURPOSE!!!
	*/
	Vertex testVertices[4];

	testVertices[0].position = Vector3f(-0.5f, 0.5f, 0.0f);
	testVertices[1].position = Vector3f(-0.5f, -0.5f, 0.0f);
	testVertices[2].position = Vector3f(0.5f, -0.5f, 0.0f);

	testVertices[0].color = Vector3f(1.0f, 0.0f, 0.0f);
	testVertices[1].color = Vector3f(0.0f, 1.0f, 0.0f);
	testVertices[2].color = Vector3f(0.0f, 0.0f, 1.0f);

	testVertices[0].texcoord = Vector2f(0.5f, 1.0f);
	testVertices[1].texcoord = Vector2f(0.0f, 0.0f);
	testVertices[2].texcoord = Vector2f(1.0f, 0.0f);


	testVertices[3].position = Vector3f(0.5f, 0.5f, 0.0f);
	testVertices[3].color = Vector3f(1.0f, 1.0f, 0.0f);
	testVertices[3].texcoord = Vector2f(0.0f, 0.0f);

	// unsigned int nbrOfVertices = sizeof(testVertices) / sizeof(Vertex);
	GLuint indices[] = { 0, 1, 2, 0, 2, 3};
	unsigned int nbrOfIndices = sizeof(indices) / sizeof(GLuint);


	/*************************/

	//VAO -> VERTEX ARRAY OBJECT
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VBO -> Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);

	//EBO -> Element Buffer Object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Vertex v;
	//auto position = v.getPosition();
	//GLvoid *pointerPosition = reinterpret_cast<GLvoid *>(&position);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	//auto color = v.getColor();
	//GLvoid *pointerColor = reinterpret_cast<GLvoid *>(&color);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//auto texcoord = v.getTexCoord();
	//GLvoid *pointerTexCoord = reinterpret_cast<GLvoid *>(&texcoord);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);


	//Textures
	// int imageWidth = 0;
	// int imageHeight = 0;
	// unsigned char *image = SOIL_load_image("srcs/textures/wood.jpg", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		updateInput();


		glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glUseProgram(coreProgram);
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, nbrOfVertices);
		glDrawElements(GL_TRIANGLES, nbrOfIndices, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glFlush();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	//glDeleteProgram(coreProgram);

    return 0;
}