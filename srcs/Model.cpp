#include "Model.hpp"

Model::Model(Vector3f position, Material *material, Texture *texDif, Texture *texSpe, std::unordered_map<std::string, Mesh*> meshes)
{
	this->position = position;
	this->material = material;
	this->overrideTexutureDiffuse = texDif;
	this->overrideTextureSpecular = texSpe;

	for(auto &i : meshes)
	{
		Mesh *cpy = new Mesh(*i.second);
		this->meshes.insert(std::make_pair(i.first, cpy));
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

void Model::render(ShaderLoader *shader)
{
	this->updateUniforms();

	this->material->sendToShader(*shader);
	
	shader->use();

	//Activate Textures
	this->overrideTexutureDiffuse->bind();
	this->overrideTextureSpecular->bind();

	for(auto &mesh : this->meshes)
		mesh.second->render(shader);
}

void Model::updateUniforms()
{

}

void Model::rotate(const Vector3f rotation)
{
	for(auto &mesh : this->meshes)
		mesh.second->rotate(rotation);
}