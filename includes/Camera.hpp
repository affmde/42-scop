#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "Vector3f.hpp"
#include "Mat4.hpp"

enum class direction_enum
{
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera(Vector3f cameraPosition, Vector3f worldUp);
	~Camera();

	const Mat4 getViewMatrix();
	const Vector3f getPosition() const;
	void handleInput(const float &dt, const double &mouseOffsetX, const double &mouseOffsetY);
	void move(const float &dt, const direction_enum direction);
	void rotate(direction_enum direction);

private:
	Mat4 viewMatrix;
	Vector3f targetPos;
	Vector3f direction;
	Vector3f worldUp;
	Vector3f position;
	Vector3f front;
	Vector3f up;
	Vector3f right;
	
	float pitch;
	float yaw;
	float roll;

	const float movementSpeed = 5.f;
	const float mouseSensitivity = 0.3f;

	void updateVectors();
	void handleMouseInput(const float &dt, const double &mouseOffsetX, const double &mouseOffsetY);
};


#endif