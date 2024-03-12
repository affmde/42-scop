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
	bool loadTexture(std::string texturePath, GLenum type, unsigned int textureUnit);
	void bind();
	void unbind();
	int getTextureUnit() const;

private:
	unsigned char *image;
	GLuint texture;
	int width;
	int heigth;
	int textureUnit;
	unsigned int type;
};

#endif