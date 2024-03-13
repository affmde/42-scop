#ifndef SCENE_HPP
# define SCENE_HPP

#include "Window.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

enum shader_enum { CORE_PROGRAM = 0 };
enum texture_enum { TEXTURE_ENUM = 0 };
enum material_enum { MATERIAL_ENUM = 0 };
enum mesh_enum { MESH_ENUM = 0 };


class Scene
{
public:
	Scene(int width, int height, std::string title);
	~Scene();

	void update();
	void render();

	bool windowShouldClose() const;
	void closeWindow();

private:
	Window window;

	std::vector<ShaderLoader*> shaders;
	std::vector<Texture*> textures;
	std::vector<Material*> materials;
	std::vector<Mesh*> meshes;
	std::vector<Vector3f*> lights;

	Mat4 viewMatrix;
	Mat4 projectionMatrix;

	Vector3f cameraPos;
	Vector3f worldUp;
	Vector3f cameraFront;
	Vector3f lightPosition;

	float fov;
	float nearPlane;
	float farPlane;

	void initGLFW();
	void initGlad();
	void initialize();
	void openGLSettings();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initMeshes();
	void initLights();
	void initUniforms();

	static void updateInput(GLFWwindow *window, Mesh &mesh);
};

#endif