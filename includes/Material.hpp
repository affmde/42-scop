#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include <string>

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "ShaderLoader.hpp"
#include "mtl_Material.hpp"

class Material
{
public:
	Material();
	Material(Vector3f ambient, Vector3f diffuse, Vector3f specular, int diffuseTex, int specularTex, float Ni, float Ns);
	Material(mtl_Material &mtl, int diffuseTex, int specularTex);
	~Material() {}

	void sendToShader(ShaderLoader &shaderProgram);
	void setAmbient(Vector3f ambient);
	void setDiffuse(Vector3f diffuse);
	void setSpecular(Vector3f specular);
	void setDiffuseTex(int diffuseTex);
	void setSpecularTex(int specularTex);
	void setNi(float Ni);
	void setNs(float Ns);
	void setDissolve(float dissolve);

	Vector3f getAmbient() const;
	Vector3f getDiffuse() const;
	Vector3f getSpecular() const;
	int getDiffuseTex() const;
	int getSpecularTex() const;
	float getNi() const;
	float getNs() const;
	float getDissolve() const;

private:
	Vector3f ambient;
	Vector3f diffuse;
	Vector3f specular;
	int diffuseTex;
	int specularTex;
	float Ni;
	float Ns;
	float dissolve;

};

std::ostream &operator<<(std::ostream &os, const Material &m);

#endif