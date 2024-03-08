#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <string>
#include <vector>

#include "Vertice.hpp"
#include "VerticeTexture.hpp"

class Vertex
{
public:
	Vertex();
	~Vertex() {}

	void addV(const Vertice v);
	void addVN(const Vertice vn);
	void addVT(const VerticeTexture vt);

	const std::vector<Vertice> &getV() const;
	const std::vector<Vertice> &getVN() const;
	const std::vector<VerticeTexture> &getVT() const;

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

private:
	std::vector<Vertice> v;
	std::vector<Vertice> vn;
	std::vector<VerticeTexture> vt;
};

#endif