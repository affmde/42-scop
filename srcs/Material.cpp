#include "Material.hpp"

Material::Material()
{
	this->ambient = Vector3f(1.f);
	this->diffuse = Vector3f(1.f);
	this->specular = Vector3f(1.f);
	this->diffuseTex = 0;
	this->specularTex = 0;
}

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

void Material::setAmbient(Vector3f ambient){ this->ambient = ambient; }
void Material::setDiffuse(Vector3f diffuse){ this->diffuse = diffuse; }
void Material::setSpecular(Vector3f specular){ this->specular = specular; }
void Material::setDiffuseTex(int diffuseTex){ this->diffuseTex = diffuseTex; }
void Material::setSpecularTex(int specularTex){ this->specularTex = specularTex; }

Vector3f Material::getAmbient()const { return this->ambient; }
Vector3f Material::getDiffuse()const { return this->diffuse; }
Vector3f Material::getSpecular()const { return this->specular; }
int Material::getDiffuseTex()const { return this->diffuseTex; }
int Material::getSpecularTex() const { return this->specularTex; }


std::ostream &operator<<(std::ostream &os, const Material &m)
{
	os << "Ambient: " << m.getAmbient() << std::endl;
	os << "Diffuse: " << m.getDiffuse() << std::endl;
	os << "Specular: " << m.getSpecular() << std::endl;
	os << "DiffuseTex: " << m.getDiffuseTex() << std::endl;
	os << "SpecularTex: " << m.getSpecularTex() << std::endl;
	return os;
}