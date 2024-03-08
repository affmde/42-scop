#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <string>
#include <vector>

#include "Vector3f.hpp"
#include "VerticeTexture.hpp"

class Vertex
{
public:
	Vertex();
	~Vertex() {}

	void addV(const Vector3f v);
	void addVN(const Vector3f vn);
	void addVT(const VerticeTexture vt);

	const std::vector<Vector3f> &getV() const;
	const std::vector<Vector3f> &getVN() const;
	const std::vector<VerticeTexture> &getVT() const;

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

private:
	std::vector<Vector3f> v;
	std::vector<Vector3f> vn;
	std::vector<VerticeTexture> vt;
};

#endif