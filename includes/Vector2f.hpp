#ifndef VECTOR2F_HPP
# define VECTOR2F_HPP

#include <ostream>

class Vector2f
{
public:
	Vector2f();
	Vector2f(float x, float y);
	Vector2f(float value);
	~Vector2f() {};

	float x;
	float y;
private:
};

std::ostream &operator<<(std::ostream &os, const Vector2f &vt);

#endif