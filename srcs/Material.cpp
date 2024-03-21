#include "Material.hpp"

Material::Material()
{
	this->ambient = Vector3f(1.f);
	this->diffuse = Vector3f(1.f);
	this->specular = Vector3f(1.f);
	this->diffuseTex = 0;
	this->specularTex = 0;
	this->Ni = 1.f;
	this->Ns = 1.f;
	this->dissolve = 1.f;
}
#include <iostream> //DELETE THIS!!!
Material::Material(mtl_Material &mtl, int diffuseTex, int specularTex)
{
	this->ambient = mtl.getAmbient();
	this->diffuse = mtl.getDiffuse();
	this->specular = mtl.getSpecular();
	this->Ni = mtl.getNi();
	this->Ns = mtl.getNs();
	this->dissolve = mtl.getDissolve();
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

Material::Material(Vector3f ambient, Vector3f diffuse, Vector3f specular, int diffuseTex, int specularTex,
	float Ni, float Ns)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
	this->Ni = Ni;
	this->Ns = Ns;
	this->dissolve = 1.f;
}

void Material::sendToShader(ShaderLoader &shaderProgram)
{
	shaderProgram.setVector3f(this->ambient, "material.ambient");
	shaderProgram.setVector3f(this->diffuse, "material.diffuse");
	shaderProgram.setVector3f(this->specular, "material.specular");
	shaderProgram.set1i(this->diffuseTex, "material.diffuseTex");
	shaderProgram.set1i(this->specularTex, "material.specularTex");
	shaderProgram.set1i(this->Ns, "material.Ns");
	shaderProgram.setFloat(this->dissolve, "material.dissolve");
}

void Material::setAmbient(Vector3f ambient){ this->ambient = ambient; }
void Material::setDiffuse(Vector3f diffuse){ this->diffuse = diffuse; }
void Material::setSpecular(Vector3f specular){ this->specular = specular; }
void Material::setDiffuseTex(int diffuseTex){ this->diffuseTex = diffuseTex; }
void Material::setSpecularTex(int specularTex){ this->specularTex = specularTex; }
void Material::setNi(float Ni){ this->Ni = Ni; }
void Material::setNs(float Ns){ this->Ns = Ns; }
void Material::setDissolve(float dissolve){ this->dissolve = dissolve; }

Vector3f Material::getAmbient()const { return this->ambient; }
Vector3f Material::getDiffuse()const { return this->diffuse; }
Vector3f Material::getSpecular()const { return this->specular; }
int Material::getDiffuseTex()const { return this->diffuseTex; }
int Material::getSpecularTex() const { return this->specularTex; }
float Material::getNi() const { return this->Ni; }
float Material::getNs() const { return this->Ns; }
float Material::getDissolve() const { return this->dissolve; }


std::ostream &operator<<(std::ostream &os, const Material &m)
{
	os << "Ambient: " << m.getAmbient() << std::endl;
	os << "Diffuse: " << m.getDiffuse() << std::endl;
	os << "Specular: " << m.getSpecular() << std::endl;
	os << "DiffuseTex: " << m.getDiffuseTex() << std::endl;
	os << "SpecularTex: " << m.getSpecularTex() << std::endl;
	return os;
}