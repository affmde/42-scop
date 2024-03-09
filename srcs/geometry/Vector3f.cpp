#include "Vector3f.hpp"

Vector3f::Vector3f() : x(0), y(0), z(0) {}
Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3f::getX() const { return this->x; }
float Vector3f::getY() const { return this->y; }
float Vector3f::getZ() const { return this->z; }

void Vector3f::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
void Vector3f::setX(float x) { this->x = x; }
void Vector3f::setY(float y) { this->y = y; }
void Vector3f::setZ(float z) { this->z = z; }

std::ostream &operator<<(std::ostream &os, const Vector3f &vec)
{
	return os << "x: " << vec.getX() << " y: " << vec.getY() << " z: " << vec.getZ();
}