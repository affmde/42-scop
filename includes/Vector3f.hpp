#ifndef VECTOR3F_HPP
# define VECTOR3F_HPP

#include <ostream>

class Vector3f
{
public:
	Vector3f();
	Vector3f(float val);
	Vector3f(float x, float y, float z);

	Vector3f operator+(const Vector3f &other);
	Vector3f operator-(const Vector3f &other);

	void set(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getX() const;
	float getY() const;
	float getZ() const;

	Vector3f cross(Vector3f &other);
	Vector3f normalize();

private:
	float x;
	float y;
	float z;
};

std::ostream &operator<<(std::ostream &os, const Vector3f &vec);
Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs);

#endif