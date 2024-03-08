#include "Vertex.hpp"

Vertex::Vertex() {}

void Vertex::addV(const Vector3f v) { this->v.push_back(v); }
void Vertex::addVN(const Vector3f vn) { this->vn.push_back(vn); }
void Vertex::addVT(const VerticeTexture vt) { this->vt.push_back(vt); }

const std::vector<Vector3f> &Vertex::getV() const { return this->v; }
const std::vector<Vector3f> &Vertex::getVN() const { return this->vn; }
const std::vector<VerticeTexture> &Vertex::getVT() const { return this->vt; }

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
	return os << "[" << vertex.v[0] << "]/[" << vertex.vt[0] << "]/[" << vertex.vn[0] << "] " << std::endl;
}