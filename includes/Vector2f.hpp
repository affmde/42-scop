#ifndef VECTOR2F_HPP
# define VECTOR2F_HPP

#include <ostream>

class Vector2f
{
public:
	Vector2f(float x, float y);
	~Vector2f() {};

	float getX() const;
	float getY() const;
private:
	float x;
	float y;
};

std::ostream &operator<<(std::ostream &os, const Vector2f &vt);

#endif