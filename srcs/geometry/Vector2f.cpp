#include "Vector2f.hpp"

Vector2f::Vector2f() : x(0), y(0) {}
Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2f::Vector2f(float value)
{
	this->x = value;
	this->y = value;
}


std::ostream &operator<<(std::ostream &os, const Vector2f &vt)
{
	return os << "x: " << vt.x << " y: " << vt.y;
}