#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <string>
#include <vector>

#include "Vector2f.hpp"
#include "VerticeTexture.hpp"

class Vertex
{
public:
	Vertex();
	~Vertex() {}

	void addV(const Vector2f v);
	void addVN(const Vector2f vn);
	void addVT(const VerticeTexture vt);

	const std::vector<Vector2f> &getV() const;
	const std::vector<Vector2f> &getVN() const;
	const std::vector<VerticeTexture> &getVT() const;

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

private:
	std::vector<Vector2f> v;
	std::vector<Vector2f> vn;
	std::vector<VerticeTexture> vt;
};

#endif