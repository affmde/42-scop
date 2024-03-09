#include "ShaderLoader.hpp"

#include <fstream>
#include <iostream>

ShaderLoader::ShaderLoader(std::string vertexPath, std::string fragmentPath)
{
	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;
}

bool ShaderLoader::loadShaders(GLuint &program)
{
	bool vertexLoaded = this->loadVertex();
	if (!vertexLoaded)
		return false;
	bool fragmentLoaded = this->loadFragment();
	if (!fragmentLoaded)
		return false;
	bool programLoaded = this->loadProgram(program);
	if (!programLoaded)
		return false;
	return true;
}

bool ShaderLoader::loadVertex()
{
	std::ifstream file;
	std::string line;
	std::string source;
	GLint success;

	file.open(this->vertexPath);
	if (file.is_open())
	{
		while(std::getline(file, line))
			source += line + "\n";
	}
	else
		std::cerr << "Error: Unable to open vertex_core.glsl" << std::endl;
	file.close();

	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vertSource = source.c_str();
	glShaderSource(this->vertexShader, 1, &vertSource, NULL);
	glCompileShader(this->vertexShader);
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->vertexShader, 512, NULL, this->infoLog);
		std::cerr << "Error: Unable to compile vertex shader" << std::endl;
		std::cout << "Infolog: " << this->infoLog << std::endl;
	}
	return success ? true : false;
}

bool ShaderLoader::loadFragment()
{
	std::ifstream file;
	std::string line;
	std::string source;
	GLint success;

	file.open(this->fragmentPath);
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			source += line + "\n";
		}
	}
	else
		std::cerr << "Error: Unable to open fragment_core.glsl" << std::endl;
	file.close();

	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragSource = source.c_str();
	glShaderSource(this->fragmentShader, 1, &fragSource, NULL);
	glCompileShader(this->fragmentShader);

	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->fragmentShader, 512, NULL, this->infoLog);
		std::cerr << "Error: Unable to compile fragment shader" << std::endl;
		std::cout << "Infolog: " << this->infoLog << std::endl;
	}
	return success ? true : false;
}

bool ShaderLoader::loadProgram(GLuint &program)
{
	GLint success;
	program = glCreateProgram();

	glAttachShader(program, this->vertexShader);
	glAttachShader(program, this->fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "Error: Unable to link program" << std::endl;
		std::cout << "Infolog: " << infoLog << std::endl;
	}

	//Clean up
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return success ? true : false;
}