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
#include "Window.hpp"

#define SPEED 0.05f


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

void handleInput(GLFWwindow *window, Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mesh.move(Vector3f(0.f, 0.f, -SPEED));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mesh.move(Vector3f(0.f, 0.f, SPEED));
	if  (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mesh.move(Vector3f(-SPEED, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mesh.move(Vector3f(SPEED, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		mesh.rotate(Vector3f(0.f, 1.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		mesh.rotate(Vector3f(0.f, -1.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		mesh.rotate(Vector3f(1.f, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		mesh.rotate(Vector3f(-1.f, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		mesh.zoom(Vector3f(SPEED));
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		mesh.zoom(Vector3f(-SPEED));
}

// GLFWwindow *createWindow(const int width, const int height, int &widthBuffer, int &heigthBuffer, std::string title)
// {

// }

int main(void)
{
    if (!glfwInit())
	{
		std::cout << "Error: glfwInit failed" << std::endl;
		return -1;
	}
	int screenWidth = 800;
	int screenHeight = 600;


	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   FOR MACOS

	Window window(screenWidth, screenHeight, "42-Scop");
	// GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "42-Scop", NULL, NULL);
	if (!window.getWindow())
	{
		std::cerr << "Failed to create a window" << std::endl;
		glfwTerminate();
		return 0;
	}

	// glfwSetFramebufferSizeCallback(window, resizeWindow);
	// glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeigth);

	// glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window.getWindow(), resizeWindow);
	glfwGetFramebufferSize(window.getWindow(), &window.getWidthBuffer(), &window.getHeigthBuffer());

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
	ShaderLoader coreProgram("srcs/shaders/vertex_core.glsl", "srcs/shaders/fragment_core.glsl");

	/*
	FOR EXEMPLE PURPOSE!!!
	*/

	Primitive primitive;

	/*************************/

	Quad quad;
	Triangle triangle;
	Mesh mesh(&triangle);

	//Textures
	Texture texture;
	texture.loadTexture("Textures/peimariSymbol.png", GL_TEXTURE_2D, 0);


	//Material
	Material material(Vector3f(0.1f), Vector3f(1.0f), Vector3f(1.f), texture.getTextureUnit(), texture.getTextureUnit());

	Vector3f position;
	Vector3f rotation;
	Vector3f scale(1.f);

	Mat4 model(1.f);

	Vector3f camPosition(0.f, 0.f, 1.f);
	Vector3f worldUp(0.f, 1.f, 0.f);
	Vector3f camFront(0.f, 0.f, -1.f);

	Mat4 viewMatrix(1.f);
	viewMatrix = lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;

	Mat4 projectionMatrix(1.f);
	projectionMatrix = perspective(fov, static_cast<float>(window.getWidthBuffer() / window.getHeigthBuffer()), nearPlane, farPlane);
	
	//LIGHTS
	Vector3f lightPos0(0.f, 0.f, 1.f);

	coreProgram.setMat4(model, "model");
	coreProgram.setMat4(viewMatrix, "viewMatrix");
	coreProgram.setMat4(projectionMatrix, "projectionMatrix");
	coreProgram.setVector3f(lightPos0, "lightPosition");
	coreProgram.setVector3f(camPosition, "cameraPos");

	while(!glfwWindowShouldClose(window.getWindow()))
	{
		glfwPollEvents();
		handleInput(window.getWindow(), mesh);
		updateInput(window.getWindow());


		glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		//Update Uniforms
		coreProgram.set1i(texture.getTextureUnit(), "texture0");
		material.sendToShader(coreProgram);

		//Move, Rotate, scale
		glfwGetFramebufferSize(window.getWindow(), &window.getWidthBuffer(), &window.getHeigthBuffer());
		projectionMatrix.reset();
		projectionMatrix = perspective(fov, static_cast<float>(window.getWidthBuffer()) / window.getHeigthBuffer(), nearPlane, farPlane);
		coreProgram.setMat4(projectionMatrix, "projectionMatrix");

		coreProgram.use();
		//Activate Textures
		texture.bind();

		mesh.render(&coreProgram);

		glfwSwapBuffers(window.getWindow());
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		texture.unbind();
	}

	glfwDestroyWindow(window.getWindow());
	glfwTerminate();
	return 0;
}