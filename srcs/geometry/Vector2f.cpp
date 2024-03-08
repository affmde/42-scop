#include "Vector2f.hpp"

Vector2f::Vector2f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector2f::getX() const { return this->x; }
float Vector2f::getY() const { return this->y; }
float Vector2f::getZ() const { return this->z; }

std::ostream &operator<<(std::ostream &os, const Vector2f &vec)
{
	return os << "x: " << vec.getX() << " y: " << vec.getY() << " z: " << vec.getZ();
}