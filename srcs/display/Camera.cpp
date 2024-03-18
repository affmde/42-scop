#include <cmath>

#include "Camera.hpp"
#include "Utils.hpp"

Camera::Camera(Vector3f cameraPosition, Vector3f worldUp) : viewMatrix(1.f)
{
	this->position = cameraPosition;
	this->worldUp = worldUp;
	this->right = Vector3f(0.f);
	this->up = worldUp;

	this->pitch = 0.f;
	this->yaw = -90.f;
	this->roll = 0.f;
	
	this->updateVectors();
}

Camera::~Camera() {}

const Mat4 Camera::getViewMatrix()
{
	this->updateVectors();
	this->viewMatrix = lookAt(this->position, this->position + this->front, this->up);
	return this->viewMatrix;
}

const Vector3f Camera::getPosition() const { return this->position; }

void Camera::updateVectors()
{
	this->front.x = cos(toRadians(this->yaw)) * cos(toRadians(this->pitch));
	this->front.y = sin(toRadians(this->pitch));
	this->front.z = sin(toRadians(this->yaw)) * cos(toRadians(this->pitch));

	this->front = normalize(this->front);
	this->right = normalize(cross(this->front, this->worldUp));
	this->up = normalize(cross(this->right, this->front));
}

void Camera::handleInput(const float &dt, const double &mouseOffsetX, const double &mouseOffsetY)
{
	this->handleMouseInput(dt, mouseOffsetX, mouseOffsetY);
}

void Camera::handleMouseInput(const float &dt, const double &mouseOffsetX, const double &mouseOffsetY)
{
	this->pitch += static_cast<float>(mouseOffsetY) * this->mouseSensitivity * dt;
	this->yaw += static_cast<float>(mouseOffsetX) * this->mouseSensitivity * dt;

	if (this->pitch > 80.f)
		this->pitch = 80.f;
	else if (this->pitch < -80.f)
		this->pitch = -80.f;
	if (this->yaw > 360.f || this->yaw < -360.f)
		this->yaw = 0;
}

void Camera::move(const float &dt, const direction_enum direction)
{
	switch(direction)
	{
		case direction_enum::FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case direction_enum::BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case direction_enum::LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case direction_enum::RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
		case direction_enum::UP:
			this->position += this->up * this->movementSpeed * dt;
			break;
		case direction_enum::DOWN:
			this->position -= this->up * this->movementSpeed * dt;
			break;
		default:
			break;
	}
}

void Camera::rotate(direction_enum direction)
{
	switch(direction)
	{
		case direction_enum::FORWARD:
			this->pitch += 1.f;
			break;
		case direction_enum::BACKWARD:
			this->pitch -= 1.f;
			break;
		case direction_enum::LEFT:
			this->yaw -= 1.f;
			break;
		case direction_enum::RIGHT:
			this->yaw += 1.f;
			break;
		default:
			break;
	}
}