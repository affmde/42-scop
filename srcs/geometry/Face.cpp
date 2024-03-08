#include "Face.hpp"

Face::Face() {}

void Face::addV(const Vertice v) { this->v.push_back(v); }
void Face::addVN(const Vertice vn) { this->vn.push_back(vn); }
void Face::addVT(const VerticeTexture vt) { this->vt.push_back(vt); }

const std::vector<Vertice> &Face::getV() const { return this->v; }
const std::vector<Vertice> &Face::getVN() const { return this->vn; }
const std::vector<VerticeTexture> &Face::getVT() const { return this->vt; }

std::ostream& operator<<(std::ostream& os, const Face& face)
{
	return os << "[" << face.v[0] << "]/[" << face.vt[0] << "]/[" << face.vn[0] << "] " << std::endl;
}