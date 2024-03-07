#include "Vertice.hpp"

Vertice::Vertice(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vertice::getX() const { return this->x; }
float Vertice::getY() const { return this->y; }
float Vertice::getZ() const { return this->z; }

std::ostream &operator<<(std::ostream &os, const Vertice &vertice)
{
	return os << "x: " << vertice.getX() << " y: " << vertice.getY() << " z: " << vertice.getZ();
}