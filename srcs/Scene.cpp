#include <iostream>

#include "Scene.hpp"
#include "Utils.hpp"
#include "Pyramid.hpp"
#include "Quad.hpp"

#define SPEED 0.05f

Scene::Scene(int width, int height, std::string title, std::string filePath) : 
	viewMatrix(1.f),
	projectionMatrix(1.f),
	camera(Vector3f(0, 0, 3.f), Vector3f(0.f, 0.f, 1.f), Vector3f(0.f, 1.f, 0.f))
{
	this->filePath = filePath;
	this->drawMode = DrawMode::LINES;
	this->cameraPos = Vector3f(0.f, 0.f, 1.f);
	this->worldUp =  Vector3f(0.f, 1.f, 0.f);
	this->cameraFront = Vector3f(0.f, 0.f, -1.f);
	this->lightPosition = Vector3f(0.f, 0.f, 1.f);

	this->fov = 45.f;
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

	this->fadeFactor = 1.f;

	try {
		this->parsedObj = parser.loadObj(this->filePath);
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

	} catch (std::exception &e) {
		throw std::runtime_error(e.what());
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
			Vector3f(2.f),
			this->textures.at("peimariSymbol")->getTextureUnit(),
			this->textures.at("peimariSymbolSpecular")->getTextureUnit()));
}

void Scene::initLights()
{
	this->lights.push_back(new Vector3f(0.f, 0.f, 1.f));
}

void Scene::initUniforms()
{
	this->shaders[CORE_PROGRAM]->setFloat(this->fadeFactor, "fadeFactor");
	this->shaders[CORE_PROGRAM]->setMat4(this->viewMatrix, "viewMatrix");
	this->shaders[CORE_PROGRAM]->setMat4(this->projectionMatrix, "projectionMatrix");
	this->shaders[CORE_PROGRAM]->setVector3f(*this->lights[0], "lightPosition");
}

void Scene::initModels()
{
	Mesh *mesh = new Mesh(
		this->parsedObj.data(),
		this->parsedObj.size(),
		NULL,
		0,
		Vector3f(0, 0.5f, 0)
	);
	this->models.push_back(new Model(
		Vector3f(0.0f, 0.f, -1.f),
		this->materials[MATERIAL_ENUM],
		this->textures.at("peimariSymbol"),
		this->textures.at("peimariSymbolSpecular"),
		std::unordered_map<std::string, Mesh*>{
			{"parsedObj", mesh}
		}
	));
}

void Scene::closeWindow() { this->window.closeWindow(); }

bool Scene::windowShouldClose() const { return this->window.windowShouldClose(); }

void Scene::update()
{
	this->updateDeltaTime();
	this->handleInput();
}

void Scene::render()
{
	glClearColor(0.13f, 0.25f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update Uniforms
	this->updateUniforms();

	for(auto &model : this->models)
		model->render(this->shaders[CORE_PROGRAM]);

	glfwSwapBuffers(window.getWindow());
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	this->textures.at("peimariSymbol")->unbind();
	this->textures.at("peimariSymbolSpecular")->unbind();
}

void Scene::updateUniforms()
{	
	if (this->isFading)
	{
		if (this->isFadeIn)
			this->fadeOut();
		else if (this->isFadeOut)
			this->fadeIn();
	}
	this->shaders[CORE_PROGRAM]->setFloat(this->fadeFactor, "fadeFactor");
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
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		this->camera.move(dt, direction_enum::UP);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		this->camera.move(dt, direction_enum::DOWN);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		this->zoom(1.f);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		this->zoom(-1.f);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		this->camera.rotate(direction_enum::LEFT);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->camera.rotate(direction_enum::RIGHT);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		this->camera.rotate(direction_enum::FORWARD);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		this->camera.rotate(direction_enum::BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->fade();
		// if (this->drawMode == DrawMode::LINES)
		// {
		// 	this->drawMode = DrawMode::TEXTURE;
		// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// }
		// else
		// {
		// 	this->drawMode = DrawMode::LINES;
		// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// }
	}
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

void Scene::zoom(float value)
{
	this->fov += value;
	if (this->fov >= this->maxFOV)
		this->fov = this->maxFOV;
	else if (this->fov <= this->minFOV)
		this->fov = this->minFOV;
}

void Scene::fade()
{
	this->isFading = true;
}
void Scene::fadeIn()
{
	if(this->fadeFactor < 1.f)
		this->fadeFactor += 0.1f;
	if (this->fadeFactor >= 1.f)
	{
		this->fadeFactor = 1.f;
		this->isFading = false;
		this->isFadeIn = true;
		this->isFadeOut = false;
	}
}

void Scene::fadeOut()
{
	if(this->fadeFactor > 0.f)
	{
		this->fadeFactor -= 0.1f;
	}
	if (this->fadeFactor <= 0.f)
	{
		this->fadeFactor = 0.f;
		this->isFading = false;
		this->isFadeOut = true;
		this->isFadeIn = false;
	}
}