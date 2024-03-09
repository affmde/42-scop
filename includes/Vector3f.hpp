#ifndef VECTOR3F_HPP
# define VECTOR3F_HPP

#include <ostream>

class Vector3f
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);

	void set(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

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