#include "Vector3f.hpp"

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3f::getX() const { return this->x; }
float Vector3f::getY() const { return this->y; }
float Vector3f::getZ() const { return this->z; }

std::ostream &operator<<(std::ostream &os, const Vector3f &vec)
{
	return os << "x: " << vec.getX() << " y: " << vec.getY() << " z: " << vec.getZ();
}