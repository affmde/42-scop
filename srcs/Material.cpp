#include "Material.hpp"

Material::Material(Vector3f ambient, Vector3f diffuse, Vector3f specular, int diffuseTex, int specularTex)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

void Material::sendToShader(ShaderLoader &shaderProgram)
{
	shaderProgram.setVector3f(this->ambient, "material.ambient");
	shaderProgram.setVector3f(this->diffuse, "material.diffuse");
	shaderProgram.setVector3f(this->specular, "material.specular");
	shaderProgram.set1i(this->diffuseTex, "material.diffuseTex");
	shaderProgram.set1i(this->specularTex, "material.specularTex");
}