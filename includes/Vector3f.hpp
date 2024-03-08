#ifndef VECTOR3F_HPP
# define VECTOR3F_HPP

#include <ostream>

class Vector3f
{
public:
	Vector3f(float x, float y, float z);
	Vector3f() {}

	float getX() const;
	float getY() const;
	float getZ() const;

private:
	float x;
	float y;
	float z;
};

std::ostream &operator<<(std::ostream &os, const Vector3f &vec);

#endif