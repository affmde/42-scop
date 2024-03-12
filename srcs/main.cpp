#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.hpp"
#include "ShaderLoader.hpp"
#include "Texture.hpp"
#include "Utils.hpp"


#define STB_IMAGE_IMPLEMENTATION
 #include "stb_images/stb_image.h"
 #define STB_IMAGE_WRITE_IMPLEMENTATION
 #include "stb_images/stb_image_write.h"

void updateInput(GLFWwindow *window)
{
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
	int frameBufferWidth, frameBufferHeigth;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeigth);

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
	testVertices[3].texcoord = Vector2f(1.0f, 1.0f);

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);


	//Textures
	Texture texture;
	texture.loadTexture("Textures/cat_mouse1.png");


	Vector3f position;
	Vector3f rotation;
	Vector3f scale(1.f);

	glm::vec3 g_position(0.f);
	glm::vec3 g_rotation(0.f);

	//Translation;
	Mat4 model(1.0f);
	model = model.translate(position);
	model = model.scale(scale);
	model = model.rotate(toRadians(0), Vector3f(1.0f, 0.0f, 0.0f));
	model = model.rotate(toRadians(2.f), Vector3f(0.0f, 1.0f, 0.0f));
	model = model.rotate(toRadians(0), Vector3f(0.0f, 0.0f, 1.0f));

	Vector3f camPosition(0.f, 0.f, 1.f);
	Vector3f worldUp(0.f, 1.f, 0.f);
	Vector3f camFront(0.f, 0.f, -1.f);

	glm::vec3 camPos(0.f, 0.f, 1.f);
	glm::vec3 wUp(0.f, 1.f, 0.f);
	glm::vec3 camFrontt(0.f, 0.f, -1.f);

	Mat4 viewMatrix(1.f);
	viewMatrix = lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;

	Mat4 projectionMatrix(1.f);
	projectionMatrix = perspective(fov, static_cast<float>(frameBufferWidth / frameBufferHeigth), nearPlane, farPlane);
	
	glUseProgram(coreProgram);

	glUniformMatrix4fv(glGetUniformLocation(coreProgram, "model"), 1, GL_FALSE, &model.model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(coreProgram, "viewMatrix"), 1, GL_FALSE, &viewMatrix.model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(coreProgram, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix.model[0][0]);

	glUseProgram(0);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		updateInput(window);


		glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glUseProgram(coreProgram);

		// //Update Uniforms
		glUniform1i(glGetUniformLocation(coreProgram, "texture0"), 0);

		//Move, Rotate, scale

		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeigth);
		projectionMatrix.reset();
		projectionMatrix = perspective(fov, static_cast<float>(frameBufferWidth) / frameBufferHeigth, nearPlane, farPlane);
		glUniformMatrix4fv(glGetUniformLocation(coreProgram, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix.model[0][0]);
		
		rotation.y += 2.f;
		position.z -= 0.01f;
		model.reset();
		Mat4 tr = model.translate(position);
		Mat4 rx = model.rotate(toRadians(rotation.x), Vector3f(1.0f, 0.0f, 0.0f));
		Mat4 ry = model.rotate(toRadians(rotation.y), Vector3f(0.0f, 1.0f, 0.0f));
		Mat4 rz = model.rotate(toRadians(rotation.z), Vector3f(0.0f, 0.0f, 1.0f));
		Mat4 sc = model.scale(scale);

		model *= tr;
		model *= rx;
		model *= ry;
		model *= rz;
		model *= sc;

		glUniformMatrix4fv(glGetUniformLocation(coreProgram, "model"), 1, GL_FALSE, &model.model[0][0]);

		// //Activate Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getTexture());
		
		glBindVertexArray(VAO);

		// //glDrawArrays(GL_TRIANGLES, 0, nbrOfVertices);
		glDrawElements(GL_TRIANGLES, nbrOfIndices, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	glfwDestroyWindow(window);
	glDeleteProgram(coreProgram);
	glfwTerminate();
	return 0;
}