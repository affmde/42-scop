#ifndef VERTICE_HPP
# define VERTICE_HPP

#include <ostream>

class Vertice
{
public:
	Vertice(float x, float y, float z);
	Vertice() {}

	float getX() const;
	float getY() const;
	float getZ() const;

private:
	float x;
	float y;
	float z;
};

std::ostream &operator<<(std::ostream &os, const Vertice &vertice);

#endif