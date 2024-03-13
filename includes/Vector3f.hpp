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

	Vector3f cross(Vector3f &other);
	Vector3f normalize();

	float x;
	float y;
	float z;
private:
};

std::ostream &operator<<(std::ostream &os, const Vector3f &vec);
Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs);
Vector3f &operator+=(Vector3f &lhs, const Vector3f &rhs);
Vector3f operator-=(const Vector3f &lhs, const Vector3f &rhs);

#endif