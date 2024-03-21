#ifndef SCENE_HPP
# define SCENE_HPP

#include <unordered_map>

#include "Window.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Parser.hpp"
#include "MtlParser.hpp"

enum shader_enum { CORE_PROGRAM = 0 };
enum texture_enum { TEXTURE_ENUM = 0 };
enum material_enum { MATERIAL_ENUM = 0 };
enum mesh_enum { MESH_ENUM = 0 };
enum class DrawMode { LINES = 0, TEXTURE = 1, COLOR = 2 };

class Scene
{
public:
	Scene(int width, int height, std::string title, std::string filePath);
	~Scene();

	void update();
	void render();

	bool windowShouldClose() const;
	void closeWindow();

private:
	Window window;

	Parser parser;
	std::unordered_map<std::string, Object*> parsedObj;
	DrawMode drawMode;

	MtlParser mtlParser;
	std::unordered_map<std::string, mtl_Material*> mtlData;

	std::vector<ShaderLoader*> shaders;
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, Material*> materials;
	std::vector<Vector3f*> lights;
	std::vector<Model*> models;
	std::string filePath;

	Mat4 viewMatrix;
	Mat4 projectionMatrix;

	Vector3f cameraPos;
	Vector3f worldUp;
	Vector3f cameraFront;
	Vector3f lightPosition;

	float fov;
	const float maxFOV = 60.f;
	const float minFOV = 1.f;
	float nearPlane;
	float farPlane;

	Camera camera;
	float dt;
	float currentTime;
	float lastTime;

	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	float fadeFactor;
	bool isFading;
	bool isFadeIn;
	bool isFadeOut;
	void fade();
	void fadeIn();
	void fadeOut();

	void initGLFW();
	void initGlad();
	void openGLSettings();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initModels();
	void initLights();
	void initUniforms();

	void updateUniforms();
	void updateDeltaTime();

	void handleInput();
	void handleKeyboardInputs();
	void handleMouseInputs();
	void zoom(float value);

	Texture &findTextureByUnit(const int unit);
};

#endif
