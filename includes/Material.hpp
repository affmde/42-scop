#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include <string>

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "ShaderLoader.hpp"

class Material
{
public:
	Material();
	Material(Vector3f ambient, Vector3f diffuse, Vector3f specular, int diffuseTex, int specularTex);
	~Material() {}

	void sendToShader(ShaderLoader &shaderProgram);
	void setAmbient(Vector3f ambient);
	void setDiffuse(Vector3f diffuse);
	void setSpecular(Vector3f specular);
	void setDiffuseTex(int diffuseTex);
	void setSpecularTex(int specularTex);

	Vector3f getAmbient() const;
	Vector3f getDiffuse() const;
	Vector3f getSpecular() const;
	int getDiffuseTex() const;
	int getSpecularTex() const;

private:
	Vector3f ambient;
	Vector3f diffuse;
	Vector3f specular;
	int diffuseTex;
	int specularTex;

};

std::ostream &operator<<(std::ostream &os, const Material &m);

#endif