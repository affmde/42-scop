#ifndef SHADERLOADER_HPP
# define SHADERLOADER_HPP

#include <string>
#include <glad/glad.h>

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "Mat4.hpp"

class ShaderLoader
{
public:
	ShaderLoader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
	~ShaderLoader();

	void use();
	void unuse();
	void set1i(int value, const char *name);
	void setVector2f(Vector2f vec, const GLchar *name);
	void setVector3f(Vector3f vec, const GLchar *name);
	void setMat4(Mat4 matrix, const char* name, bool transpose = GL_FALSE);
	void setFloat(float value, const GLchar *name);

private:
	unsigned int program;
	std::string vertexPath;
	std::string fragmentPath;
	std::string geometryPath;

	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;

	std::string loadShaderSource(std::string filePath);
	GLuint loadShader(GLenum type, std::string source);
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

};

#endif // SHADERLOADER_HPP