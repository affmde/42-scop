#ifndef SHADERLOADER_HPP
# define SHADERLOADER_HPP

#include <string>
#include <glad/glad.h>

class ShaderLoader
{
public:
	ShaderLoader(std::string vertexPath, std::string fragmentPath);
	~ShaderLoader() {}

	bool loadShaders(GLuint &program);

private:
	std::string vertexPath;
	std::string fragmentPath;
	GLuint vertexShader;
	GLuint fragmentShader;
	char infoLog[512];

	bool loadVertex();
	bool loadFragment();
	bool loadProgram(GLuint &program);

};

#endif // SHADERLOADER_HPP