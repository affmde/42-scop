#include <iostream>

#include "Scene.hpp"
#include "Utils.hpp"
#include "Quad.hpp"

#define SPEED 0.05f


Scene::Scene(int width, int height, std::string title) : 
	viewMatrix(1.f),
	projectionMatrix(1.f)
{
	this->cameraPos = Vector3f(0.f, 0.f, 1.f);
	this->worldUp =  Vector3f(0.f, 1.f, 0.f);
	this->cameraFront = Vector3f(0.f, 0.f, -1.f);
	this->lightPosition = Vector3f(0.f, 0.f, 1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 100.f;

	try {
		this->initGLFW();
		this->window.createWindow(width, height, title);
		this->initGlad();
		this->openGLSettings();
		this->initMatrices();
		this->initShaders();
		this->initTextures();
		this->initMaterials();
		this->initMeshes();
		this->initLights();
		this->initUniforms();
	} catch (std::string &e) {
		std::cerr << e << std::endl;
	}
}
Scene::~Scene()
{
	glfwTerminate();
	for(auto &shader : this->shaders)
		delete shader;
	for(auto &texture : this->textures)
		delete texture;
	for(auto &material : this->materials)
		delete material;
	for(auto &mesh : this->meshes)
		delete mesh;
	for(auto &light : this->lights)
		delete light;
}

void Scene::initialize() {}

void Scene::initGLFW()
{
	if (!glfwInit())
		throw "Error: Failed to initialize GLFW";
}

void Scene::initGlad()
{
	if (!gladLoadGL())
	{
		glfwTerminate();
		throw "Error: Failed to initialize GLAD";
	}
}

void Scene::openGLSettings()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Scene::initMatrices()
{
	this->viewMatrix = lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->worldUp);
	this->projectionMatrix = perspective(
		this->fov,
		static_cast<float>(this->window.getWidthBuffer() / this->window.getHeigthBuffer()),
		this->nearPlane,
		this->farPlane
	);
}

void Scene::initShaders()
{
	this->shaders.push_back(new ShaderLoader("srcs/shaders/vertex_core.glsl", "srcs/shaders/fragment_core.glsl"));
}

void Scene::initTextures()
{
	Texture *texture = new Texture();
	texture->loadTexture("Textures/peimariSymbol.png", GL_TEXTURE_2D, 0);
	this->textures.push_back(texture);
}

void Scene::initMaterials()
{
	  this->materials.push_back(
		new Material(
			Vector3f(0.1f),
			Vector3f(1.0f),
			Vector3f(1.f),
			this->textures[TEXTURE_ENUM]->getTextureUnit(),
			this->textures[TEXTURE_ENUM]->getTextureUnit()));
}

void Scene::initMeshes()
{
	Quad quad;
	this->meshes.push_back(new Mesh(&quad));
}

void Scene::initLights()
{
	this->lights.push_back(new Vector3f(0.f, 0.f, 1.f));
}

void Scene::initUniforms()
{
	this->shaders[CORE_PROGRAM]->setMat4(this->viewMatrix, "viewMatrix");
	this->shaders[CORE_PROGRAM]->setMat4(this->projectionMatrix, "projectionMatrix");
	this->shaders[CORE_PROGRAM]->setVector3f(*this->lights[0], "lightPosition");
	this->shaders[CORE_PROGRAM]->setVector3f(this->cameraPos, "cameraPos");
}

void Scene::closeWindow() { this->window.closeWindow(); }

bool Scene::windowShouldClose() const { return this->window.windowShouldClose(); }

void Scene::update()
{
	glfwPollEvents();
	this->updateInput(this->window.getWindow(), *this->meshes[MESH_ENUM]);
}

void Scene::render()
{
	glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update Uniforms
	this->shaders[CORE_PROGRAM]->set1i(this->textures[TEXTURE_ENUM]->getTextureUnit(), "texture0");
	this->materials[MATERIAL_ENUM]->sendToShader(*this->shaders[CORE_PROGRAM]);

	//Move, Rotate, scale
	glfwGetFramebufferSize(this->window.getWindow(), &this->window.getWidthBuffer(), &this->window.getHeigthBuffer());

	projectionMatrix.reset();
	projectionMatrix = perspective(fov, static_cast<float>(window.getWidthBuffer()) / window.getHeigthBuffer(), nearPlane, farPlane);
	this->shaders[CORE_PROGRAM]->setMat4(projectionMatrix, "projectionMatrix");
	this->shaders[CORE_PROGRAM]->use();

	//Activate Textures
	this->textures[TEXTURE_ENUM]->bind();

	this->meshes[MESH_ENUM]->render(this->shaders[CORE_PROGRAM]);

	glfwSwapBuffers(window.getWindow());
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	//texture.unbind();
}

void Scene::updateInput(GLFWwindow *window, Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mesh.move(Vector3f(0.f, 0.f, -SPEED));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mesh.move(Vector3f(0.f, 0.f, SPEED));
	if  (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mesh.move(Vector3f(-SPEED, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mesh.move(Vector3f(SPEED, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		mesh.rotate(Vector3f(0.f, 1.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		mesh.rotate(Vector3f(0.f, -1.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		mesh.rotate(Vector3f(1.f, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		mesh.rotate(Vector3f(-1.f, 0.f, 0.f));
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		mesh.zoom(Vector3f(SPEED));
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		mesh.zoom(Vector3f(-SPEED));
}