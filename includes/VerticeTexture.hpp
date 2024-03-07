#ifndef VERTICE_TEXTURE_HPP
# define VERTICE_TEXTURE_HPP

#include <ostream>

class VerticeTexture
{
public:
	VerticeTexture(float x, float y);
	~VerticeTexture() {};

	float getX() const;
	float getY() const;
private:
	float x;
	float y;
};

std::ostream &operator<<(std::ostream &os, const VerticeTexture &vt);

#endif