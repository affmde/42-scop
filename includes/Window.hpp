#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.hpp"

class Window
{
public:
	Window();
	~Window();

	GLFWwindow *getWindow();
	int &getWidthBuffer();
	int &getHeigthBuffer();

	GLFWwindow *createWindow(const int width, const int heigth, std::string title);
	void closeWindow();

	bool windowShouldClose() const;

private:
	GLFWwindow *window;
	int widthBuffer;
	int heigthBuffer;
	std::string title;
};

#endif
