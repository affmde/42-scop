#include "Vertex.hpp"

Vertex::Vertex() {}

void Vertex::addV(const Vertice v) { this->v.push_back(v); }
void Vertex::addVN(const Vertice vn) { this->vn.push_back(vn); }
void Vertex::addVT(const VerticeTexture vt) { this->vt.push_back(vt); }

const std::vector<Vertice> &Vertex::getV() const { return this->v; }
const std::vector<Vertice> &Vertex::getVN() const { return this->vn; }
const std::vector<VerticeTexture> &Vertex::getVT() const { return this->vt; }

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
	return os << "[" << vertex.v[0] << "]/[" << vertex.vt[0] << "]/[" << vertex.vn[0] << "] " << std::endl;
}