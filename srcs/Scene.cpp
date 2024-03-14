#include <iostream>

#include "Scene.hpp"
#include "Utils.hpp"
#include "Pyramid.hpp"
#include "Quad.hpp"

#define SPEED 0.05f


Scene::Scene(int width, int height, std::string title) : 
	viewMatrix(1.f),
	projectionMatrix(1.f),
	camera(Vector3f(0, 0, 1.f), Vector3f(0.f, 0.f, 1.f), Vector3f(0.f, 1.f, 0.f))
{
	this->cameraPos = Vector3f(0.f, 0.f, 1.f);
	this->worldUp =  Vector3f(0.f, 1.f, 0.f);
	this->cameraFront = Vector3f(0.f, 0.f, -1.f);
	this->lightPosition = Vector3f(0.f, 0.f, 1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 100.f;

	this->dt = 0;
	this->currentTime = 0;
	this->lastTime = 0;

	this->lastMouseX = 0;
	this->lastMouseY = 0;
	this->mouseX = 0;
	this->mouseY = 0;
	this->mouseOffsetX = 0;
	this->mouseOffsetY = 0;
	this->firstMouse = true;

	try {
		this->initGLFW();
		this->window.createWindow(width, height, title);
		this->initGlad();
		this->openGLSettings();
		this->initMatrices();
		this->initShaders();
		this->initTextures();
		this->initMaterials();
		this->initModels();
		this->initLights();
		this->initUniforms();
	} catch (std::string &e) {
		std::cerr << e << std::endl;
	}
}
Scene::~Scene()
{
	for(auto &shader : this->shaders)
		delete shader;
	for(auto &texture : this->textures)
		delete texture.second;
	for(auto &material : this->materials)
		delete material;
	for(auto &light : this->lights)
		delete light;
	for(auto &model : this->models)
		delete model;
	glfwTerminate();
}

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
	GLFWwindow *window = this->window.getWindow();
	//TODO: REMEMBER TO UNCOMMENT THE NEXT LINE IN MAC!!!!!!!!!!
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	this->textures.insert(std::make_pair("peimariSymbol",texture));
	Texture *texture2 = new Texture();
	texture2->loadTexture("Textures/peimariSymbolSpecular.png", GL_TEXTURE_2D, 1);
	this->textures.insert(std::make_pair("peimariSymbolSpecular", texture2));
}

void Scene::initMaterials()
{
	  this->materials.push_back(
		new Material(
			Vector3f(0.1f),
			Vector3f(1.0f),
			Vector3f(1.f),
			this->textures.at("peimariSymbol")->getTextureUnit(),
			this->textures.at("peimariSymbolSpecular")->getTextureUnit()));
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
}

void Scene::initModels()
{
	std::unordered_map<std::string, Mesh*> meshes;
	Pyramid pyramid;
	Mesh *mesh = new Mesh(&pyramid);
	meshes.insert(std::make_pair("pyramid", mesh));
	

	Quad quad;
	Mesh *mesh2 = new Mesh(&quad);
	meshes.insert(std::make_pair("quad", mesh2));

	this->models.push_back(new Model(
		Vector3f(0.f),
		this->materials[MATERIAL_ENUM],
		this->textures.at("peimariSymbol"),
		this->textures.at("peimariSymbolSpecular"),
		meshes
	));

	this->models.push_back(new Model(
		Vector3f(0.f),
		this->materials[MATERIAL_ENUM],
		this->textures.at("peimariSymbol"),
		this->textures.at("peimariSymbolSpecular"),
		meshes
	));

	for(auto &mesh : meshes)
		delete mesh.second;
	meshes.clear();
}

void Scene::closeWindow() { this->window.closeWindow(); }

bool Scene::windowShouldClose() const { return this->window.windowShouldClose(); }

void Scene::update()
{
	this->updateDeltaTime();
	this->handleInput();
	for(auto &model : this->models)
		model->rotate(Vector3f(0.f, 1.f, 0.f));
}

void Scene::render()
{
	glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update Uniforms
	this->updateUniforms();

	// this->materials[MATERIAL_ENUM]->sendToShader(*this->shaders[CORE_PROGRAM]);
	
	// this->shaders[CORE_PROGRAM]->use();

	// //Activate Textures
	// this->textures.at("peimariSymbol")->bind();
	// this->textures.at("peimariSymbolSpecular")->bind();

	// this->meshes["pyramid"]->render(this->shaders[CORE_PROGRAM]);

	this->models[0]->render(this->shaders[CORE_PROGRAM]);
	this->models[1]->render(this->shaders[CORE_PROGRAM]);

	glfwSwapBuffers(window.getWindow());
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	this->textures.at("peimariSymbol")->unbind();
	this->textures.at("peimariSymbolSpecular")->unbind();
}

void Scene::updateUniforms()
{	
	//Move, Rotate, scale
	this->viewMatrix = this->camera.getViewMatrix();
	this->shaders[CORE_PROGRAM]->setMat4(this->viewMatrix, "viewMatrix");
	this->shaders[CORE_PROGRAM]->setVector3f(this->camera.getPosition(), "cameraPos");

	glfwGetFramebufferSize(this->window.getWindow(), &this->window.getWidthBuffer(), &this->window.getHeigthBuffer());

	projectionMatrix.reset();
	projectionMatrix = perspective(
		this->fov,
		static_cast<float>(this->window.getWidthBuffer()) / this->window.getHeigthBuffer(),
		this->nearPlane, farPlane);
	this->shaders[CORE_PROGRAM]->setMat4(projectionMatrix, "projectionMatrix");
}

void Scene::updateDeltaTime()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	this->dt = this->currentTime - this->lastTime;
	this->lastTime = this->currentTime;
}

void Scene::handleInput()
{
	glfwPollEvents();
	
	this->handleKeyboardInputs();
	this->handleMouseInputs();
	this->camera.handleInput(this->dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Scene::handleKeyboardInputs()
{
	GLFWwindow *window = this->window.getWindow();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		this->camera.move(this->dt, direction_enum::FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		this->camera.move(dt, direction_enum::BACKWARD);
	if  (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->camera.move(dt, direction_enum::LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->camera.move(dt, direction_enum::RIGHT);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		this->cameraPos.y -= SPEED;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->cameraPos.y += SPEED;
}

void Scene::handleMouseInputs()
{
	glfwGetCursorPos(this->window.getWindow(), &this->mouseX, &this->mouseY);
	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}