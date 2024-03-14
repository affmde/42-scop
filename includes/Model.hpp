#ifndef MODEL_HPP
# define MODEL_HPP

#include <unordered_map>

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "ShaderLoader.hpp"

class Model
{
public:
	Model(Vector3f position, Material *material, Texture *texDif, Texture *texSpe, std::unordered_map<std::string, Mesh*> meshes);
	~Model();

	void update();
	void render(ShaderLoader *shader);

	void rotate(const Vector3f rotation);

private:
	Material *material;
	Texture *overrideTexutureDiffuse;
	Texture *overrideTextureSpecular;
	std::unordered_map<std::string, Mesh*> meshes;

	Vector3f origin;
	Vector3f position;

	void updateUniforms();
};

#endif