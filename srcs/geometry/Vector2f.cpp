#include "Vector2f.hpp"

Vector2f::Vector2f() : x(0), y(0) {}
Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2f::set(float x, float y)
{
	this->x = x;
	this->y = y;
}
void Vector2f::setX(float x) { this->x = x; }
void Vector2f::setY(float y) { this->y = y; }

float Vector2f::getX() const { return this->x; }
float Vector2f::getY() const { return this->y; }

std::ostream &operator<<(std::ostream &os, const Vector2f &vt)
{
	return os << "x: " << vt.getX() << " y: " << vt.getY();
}