#include "Texture.hpp"

#include <iostream>
#include "BMP.hpp"

Texture::Texture()
{
	this->width = 0;
	this->heigth = 0;
}

Texture::~Texture()
{
	// glDeleteTextures(1, &this->texture);
}

GLuint Texture::getTexture() const { return this->texture; }
#include <cstring>
bool Texture::loadTexture(std::string texturePath, GLenum type, unsigned int textureUnit)
{
	this->textureUnit = textureUnit;
	this->type = type;

	glGenTextures(1, &this->texture);
	glBindTexture(type, this->texture);

	BMP bmp(texturePath);
	this->image = bmp.getData();
	this->width = bmp.getWidth();
	this->heigth = bmp.getHeight();

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (!this->image)
	{
		std::cout << "Failed to load the image" << std::endl;
		return false;
	}
	else
	{
		glTexImage2D(type, 0, GL_RGB, this->width, this->heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, this->image);
		glGenerateMipmap(type);
	}
	this->bind();
	return true;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + this->textureUnit);
	glBindTexture(this->type, this->texture);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}

int Texture::getTextureUnit() const { return this->textureUnit; }