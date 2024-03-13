#include <iostream>

#include "Window.hpp"

Window::Window(const int width, const int heigth, std::string title)
	: width(width), heigth(heigth), title(title)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   FOR MACOS
	this->window = glfwCreateWindow(width, heigth, title.c_str(), NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
}

Window::~Window() {}

int &Window::getWidthBuffer() { return this->widthBuffer; }
int &Window::getHeigthBuffer() { return this->heigthBuffer; }


void Window::resizeWindow(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

GLFWwindow *Window::getWindow() { return this->window; }