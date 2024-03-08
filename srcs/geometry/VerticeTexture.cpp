#include "VerticeTexture.hpp"

VerticeTexture::VerticeTexture(float x, float y)
{
	this->x = x;
	this->y = y;
}

float VerticeTexture::getX() const { return this->x; }
float VerticeTexture::getY() const { return this->y; }

std::ostream &operator<<(std::ostream &os, const VerticeTexture &vt)
{
	return os << "x: " << vt.getX() << " y: " << vt.getY();
}