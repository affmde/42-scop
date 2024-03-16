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
	Model(Vector3f position, Material *material, Texture *textDif, Texture *texSpe, std::string fileName);
	~Model();

	void update();
	void render(ShaderLoader *shader);

	void rotate(const Vector3f rotation);
	void setSelfRotate();

	bool getSelfRotate() const;

private:
	Material *material;
	Texture *overrideTexutureDiffuse;
	Texture *overrideTextureSpecular;
	std::unordered_map<std::string, Mesh*> meshes;

	Vector3f origin;
	Vector3f position;
	bool selfRotate;
};

#endif