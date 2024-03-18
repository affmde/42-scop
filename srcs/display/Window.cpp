#include <iostream>

#include "Window.hpp"

void resizeWindow(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

Window::Window() {}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}

GLFWwindow *Window::createWindow(const int width, const int heigth, std::string title)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   FOR MACOS
	this->window = glfwCreateWindow(width, heigth, title.c_str(), NULL, NULL);
	if (!this->window)
	{
		throw "Failed to create window";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->widthBuffer, &this->heigthBuffer);
	glfwSetFramebufferSizeCallback(this->window, resizeWindow);

	glfwMakeContextCurrent(window);
	return this->window;
}


void Window::closeWindow() { glfwSetWindowShouldClose(this->window, true); }

int &Window::getWidthBuffer() { return this->widthBuffer; }
int &Window::getHeigthBuffer() { return this->heigthBuffer; }
bool Window::windowShouldClose() const { return glfwWindowShouldClose(this->window); }

GLFWwindow *Window::getWindow() { return this->window; }