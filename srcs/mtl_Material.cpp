#include "mtl_Material.hpp"

mtl_Material::mtl_Material()
{
	this->ambient = Vector3f(1.f);
	this->diffuse = Vector3f(1.f);
	this->specular = Vector3f(1.f);
}
mtl_Material::~mtl_Material(){}

void mtl_Material::setAmbient(Vector3f ambient) { this->ambient = ambient; }
void mtl_Material::setDiffuse(Vector3f diffuse) { this->diffuse = diffuse; }
void mtl_Material::setSpecular(Vector3f specular) { this->specular = specular; }
void mtl_Material::setDiffuseTex(std::string diffuseTex) { this->diffuseTex = diffuseTex; }
void mtl_Material::setSpecularTex(std::string specularTex) { this->specularTex = specularTex; }
void mtl_Material::setNi(float Ni) { this->Ni = Ni; }
void mtl_Material::setDissolve(float dissolve) { this->dissolve = dissolve; }
void mtl_Material::setNs(float Ns) { this->Ns = Ns; }

Vector3f mtl_Material::getAmbient() const { return this->ambient; }
Vector3f mtl_Material::getDiffuse() const { return this->diffuse; }
Vector3f mtl_Material::getSpecular() const { return this->specular; }
std::string mtl_Material::getDiffuseTex() const { return this->diffuseTex; }
std::string mtl_Material::getSpecularTex() const { return this->specularTex; }
float mtl_Material::getNi() const { return this->Ni; }
float mtl_Material::getDissolve() const { return this->dissolve; }
float mtl_Material::getNs() const { return this->Ns; }