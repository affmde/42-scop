#include <cmath>

#include "Utils.hpp"

std::vector<std::string> str_split(std::string line, std::string delimeter)
{
	std::vector<std::string> vector;
	size_t pos = 0;
	std::string token;
	while((pos = line.find(delimeter)) != std::string::npos)
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimeter.length());
		vector.push_back(token);
	}
	if (!line.empty())
		vector.push_back(line);
	return vector;
}

float toRadians(int deg) { return (deg * M_PI) / 180; }
float dot(const Vector3f &a, const Vector3f &b)
{
	return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}

Mat4 lookAt(const Vector3f &camPosition, const Vector3f &targetPosition, Vector3f worldUp)
{
	// Vector3f forward = (targetPosition - camPosition).normalize();
	// Vector3f rigth = (worldUp.cross(forward)).normalize();
	// Vector3f up = forward.cross(rigth);

	Vector3f forward = normalize(camPosition - targetPosition);
	Vector3f rigth = normalize(cross(worldUp, forward));
	Vector3f up = cross(forward, rigth);

	Mat4 viewMatrix(1.f);
	viewMatrix.model[0][0] = rigth.getX();
	viewMatrix.model[1][0] = rigth.getY();
	viewMatrix.model[2][0] = rigth.getZ();
	viewMatrix.model[3][0] = -dot(rigth, camPosition);

	viewMatrix.model[0][1] = up.getX();
	viewMatrix.model[1][1] = up.getY();
	viewMatrix.model[2][1] = up.getZ();
	viewMatrix.model[3][1] = -dot(up, camPosition);

	viewMatrix.model[0][2] = forward.getX();
	viewMatrix.model[1][2] = forward.getY();
	viewMatrix.model[2][2] = forward.getZ();
	viewMatrix.model[3][2] = -dot(forward, camPosition);

	return viewMatrix;
}

Mat4 perspective(float fov, float aspect, float zNear, float zFar)
{
	Mat4 perspective(1.f);
	float tanHalfFov = tanf(toRadians(fov / 2.0f));
	perspective.model[0][0] = 1.f / (aspect * tanHalfFov);
	perspective.model[1][1] = 1.f / tanHalfFov;
	perspective.model[2][2] = -(zFar + zNear) / (zFar - zNear);
	perspective.model[2][3] = -1.f;
	perspective.model[3][2] = -(2 * zFar * zNear) / (zFar - zNear);
	perspective.model[3][3] = 0;
	return perspective;
}

Vector3f normalize(const Vector3f &a)
{
	float magnitude = std::sqrt(a.getX() * a.getX() + a.getY() * a.getY() + a.getZ() * a.getZ());

    // Avoid division by zero by checking if magnitude is not zero
    if (magnitude != 0) {
        return Vector3f(a.getX() / magnitude, a.getY() / magnitude, a.getZ() / magnitude);
    } else {
        // If magnitude is zero, return a zero vector or handle appropriately
        return Vector3f(0.f, 0.f, 0.f);
    }
}

Vector3f cross(Vector3f &a, Vector3f &b)
{
	return Vector3f(a.getY() * b.getZ() - a.getZ() * b.getY(),
					a.getZ() * b.getX() - a.getX() * b.getZ(),
					a.getX() * b.getY() - a.getY() * b.getX());
}