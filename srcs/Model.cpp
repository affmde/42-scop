#include "Model.hpp"
#include "Parser.hpp"

Model::Model(Vector3f position, Material *material, Texture *texDif, Texture *texSpe, std::unordered_map<std::string, Mesh*> meshes)
{
	this->position = position;
	this->material = material;
	this->overrideTexutureDiffuse = texDif;
	this->overrideTextureSpecular = texSpe;
	this->selfRotate = false;

	for(auto &i : meshes)
	{
		Mesh *cpy = new Mesh(*i.second);
		this->meshes.insert(std::make_pair(i.first, cpy));
	}
	for(auto &i : this->meshes)
	{
		i.second->move(this->position);
	}
}


Model::~Model()
{
	for(auto &i : this->meshes)
		delete i.second;
}

void Model::update()
{
}
#include <iostream>
void Model::render(ShaderLoader *shader)
{
	if (this->selfRotate)
		this->rotate(Vector3f(0.f, 1.f, 0.f));
	this->material->sendToShader(*shader);
	
	shader->use();

	//Activate Textures

	for(auto &mesh : this->meshes)
	{
		this->overrideTexutureDiffuse->bind();
		this->overrideTextureSpecular->bind();
		mesh.second->render(shader);
	}
}

void Model::rotate(const Vector3f rotation)
{
	for(auto &mesh : this->meshes)
		mesh.second->rotate(rotation);
}
void Model::setSelfRotate() { this->selfRotate = !this->selfRotate; }
bool Model::getSelfRotate() const { return this->selfRotate; }