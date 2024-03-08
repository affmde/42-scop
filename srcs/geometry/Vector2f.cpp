#include "Vector2f.hpp"

Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2f::getX() const { return this->x; }
float Vector2f::getY() const { return this->y; }

std::ostream &operator<<(std::ostream &os, const Vector2f &vt)
{
	return os << "x: " << vt.getX() << " y: " << vt.getY();
}