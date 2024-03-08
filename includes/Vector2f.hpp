#ifndef VECTOR2F_HPP
# define VECTOR2F_HPP

#include <ostream>

class Vector2f
{
public:
	Vector2f(float x, float y, float z);
	Vector2f() {}

	float getX() const;
	float getY() const;
	float getZ() const;

private:
	float x;
	float y;
	float z;
};

std::ostream &operator<<(std::ostream &os, const Vector2f &vec);

#endif