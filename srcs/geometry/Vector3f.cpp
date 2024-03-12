#include <cmath>

#include "Vector3f.hpp"

Vector3f::Vector3f() : x(0), y(0), z(0) {}
Vector3f::Vector3f(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;

}
Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f Vector3f::operator+(const Vector3f &other)
{
	return (Vector3f(this->x + other.x, this->y + other.y, this->z + other.z));
}

Vector3f Vector3f::operator-(const Vector3f &other)
{
	return (Vector3f(this->x - other.x, this->y - other.y, this->z - other.z));
}
Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs)
{
	return (Vector3f(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ()));
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

Vector3f Vector3f::cross(Vector3f &other)
{
	return (Vector3f(
		this->y * other.z - this->z * other.y,
		this->z * other.x - this->x * other.z,
		this->x * other.y - this->y * other.x)
	);
}
Vector3f Vector3f::normalize()
{
	float length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	return (Vector3f(this->x / length, this->y / length, this->z / length));
}