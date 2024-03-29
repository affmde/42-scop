#include "ShaderLoader.hpp"

#include <fstream>
#include <iostream>

ShaderLoader::ShaderLoader(std::string vertexPath,  std::string fragmentPath, std::string geometryPath)
{
	this->vertexShader = 0;
	this->geometryShader = 0;
	this->fragmentShader = 0;

	this->vertexShader = this->loadShader(GL_VERTEX_SHADER, vertexPath);
	if (geometryPath != "")
		this->geometryShader = this->loadShader(GL_GEOMETRY_SHADER, geometryPath);
	this->fragmentShader = this->loadShader(GL_FRAGMENT_SHADER, fragmentPath);

	this->linkProgram(this->vertexShader, this->geometryShader, this->fragmentShader);
	//Clean up
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}
ShaderLoader::~ShaderLoader()
{
	// glDeleteShader(this->program);
}

std::string ShaderLoader::loadShaderSource(std::string filePath)
{
	std::ifstream file;
	std::string line;
	std::string source;

	file.open(filePath);
	if (file.is_open())
	{
		while(std::getline(file, line))
			source += line + "\n";
	}
	else
		std::cerr << "Error: Unable to open " << filePath << std::endl;
	file.close();

	return source;
}

GLuint ShaderLoader::loadShader(GLenum type, std::string filePath)
{
	GLint success;
	char infoLog[512];
	GLuint shader = glCreateShader(type);
	std::string src = this->loadShaderSource(filePath);
	const GLchar *source = src.c_str();
	
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Error: Unable to compile vertex shader: " << filePath << std::endl;
		std::cout << "Infolog: " << infoLog << std::endl;
	}
	return shader;
}

void ShaderLoader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
{
	GLint success;
	char infoLog[512];
	this->program = glCreateProgram();

	glAttachShader(this->program, vertexShader);
	if (geometryShader)
		glAttachShader(this->program, geometryShader);
	glAttachShader(this->program, fragmentShader);

	glLinkProgram(this->program);

	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cerr << "Error: Unable to link program" << std::endl;
		std::cout << "Infolog: " << infoLog << std::endl;
	}

	glUseProgram(0);
}

void ShaderLoader::use() { glUseProgram(this->program); }
void ShaderLoader::unuse() { glUseProgram(0); }
void ShaderLoader::setVector2f(Vector2f vec, const char *name)
{
	this->use();
	glUniform2fv(glGetUniformLocation(this->program, name), 1, reinterpret_cast<GLfloat*>(&vec));
	this->unuse();
}
void ShaderLoader::setVector3f(Vector3f vec, const GLchar *name)
{
	this->use();
	glUniform3fv(glGetUniformLocation(this->program, name), 1, reinterpret_cast<GLfloat*>(&vec));
	this->unuse();
}
void ShaderLoader::setMat4(Mat4 matrix, const char *name, bool transpose)
{
	this->use();
	glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, transpose, &matrix.model[0][0]);
	this->unuse();
}
void ShaderLoader::set1i(int value, const char *name)
{
	this->use();
	glUniform1i(glGetUniformLocation(this->program, name), value);
	this->unuse();
}
void ShaderLoader::setFloat(float value, const GLchar *name)
{
	this->use();
	glUniform1f(glGetUniformLocation(this->program, name), value);
	this->unuse();
}