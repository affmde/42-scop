#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.hpp"

class Window
{
public:
	Window(const int width, const int heigth, std::string title);
	~Window();
	
	void resizeWindow(GLFWwindow *window, int width, int heigth);
	GLFWwindow *getWindow();
	int &getWidthBuffer();
	int &getHeigthBuffer();

private:
	GLFWwindow *window;
	int width;
	int heigth;
	int widthBuffer;
	int heigthBuffer;
	std::string title;
};

#endif