#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include <Mat4.hpp>


class Texture
{
public:
	Texture();
	~Texture();

	GLuint getTexture() const;
	bool loadTexture(std::string texturePath);

private:
	unsigned char *image;
	GLuint texture;
	int width;
	int heigth;
	Mat4 model;
};

#endif