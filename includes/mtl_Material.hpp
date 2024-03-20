#ifndef MTL_MATERIAL_HPP
# define MTL_MATERIAL_HPP

#include <string>

#include "Vector3f.hpp"

class mtl_Material
{
public:
	mtl_Material();
	~mtl_Material();

	void setAmbient(Vector3f ambient);
	void setDiffuse(Vector3f diffuse);
	void setSpecular(Vector3f specular);
	void setDiffuseTex(std::string diffuseTex);
	void setSpecularTex(std::string specularTex);
	void setNi(float Ni);
	void setDissolve(float dissolve);
	void setNs(float Ns);

	Vector3f getAmbient() const;
	Vector3f getDiffuse() const;
	Vector3f getSpecular() const;
	std::string getDiffuseTex() const;
	std::string getSpecularTex() const;
	float getNi() const;
	float getDissolve() const;
	float getNs() const;

private:
	Vector3f ambient;
	Vector3f diffuse;
	Vector3f specular;
	std::string diffuseTex;
	std::string specularTex;
	float Ni;
	float dissolve;
	float Ns;
	
};

#endif
