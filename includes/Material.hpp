#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "ShaderLoader.hpp"

class Material
{
public:
	Material(Vector3f ambient, Vector3f diffuse, Vector3f specular, int diffuseTex, int specularTex);
	~Material() {}

	void sendToShader(ShaderLoader &shaderProgram);

private:
	Vector3f ambient;
	Vector3f diffuse;
	Vector3f specular;
	int diffuseTex;
	int specularTex;

};


#endif