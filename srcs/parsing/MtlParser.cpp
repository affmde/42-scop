#include <fstream>
#include <sstream>
#include <iostream> //DELETE THIS!!!!!

#include "MtlParser.hpp"

MtlParser::MtlParser() {}
MtlParser::~MtlParser() {}

std::unordered_map<std::string, mtl_Material*> MtlParser::parseMtlFile(std::string mtlFile)
{
	std::ifstream file(mtlFile);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + mtlFile);
	std::string line;
	std::unordered_map<std::string, mtl_Material*> materials;
	std::string currentMtl;
	std::istringstream iss;
	while (std::getline(file, line))
	{
		iss.clear();
		std::string token;
		iss.str(line);
		iss >> token;
		if (token == "newmtl")
		{
			iss >> currentMtl;
			materials[currentMtl] = new mtl_Material();
		}
		else if (token == "Ka")
		{
			float r, g, b;
			iss >> r >> g >> b;
			materials[currentMtl]->setAmbient(Vector3f(r, g, b));
		}
		else if (token == "Kd")
		{
			float r, g, b;
			iss >> r >> g >> b;
			materials[currentMtl]->setDiffuse(Vector3f(r, g, b));
		}
		else if (token == "Ks")
		{
			float r, g, b;
			iss >> r >> g >> b;
			materials[currentMtl]->setSpecular(Vector3f(r, g, b));
		}
		else if (token == "Ni")
		{
			float Ni;
			iss >> Ni;
			materials[currentMtl]->setNi(Ni);
		}
		else if (token == "Ns")
		{
			float Ns;
			iss >> Ns;
			materials[currentMtl]->setNs(Ns);
		}
		else if (token == "d")
		{
			float dissolve;
			iss >> dissolve;
			materials[currentMtl]->setDissolve(dissolve);
		}
		else if (token == "Tr")
		{
			float tr;
			iss >> tr;
			materials[currentMtl]->setDissolve(1.f - tr);
		}
		else if (token == "map_Kd")
		{
			std::string tex;
			iss >> tex;
			materials[currentMtl]->setDiffuseTex(tex);
		}
		else if (token == "map_Ks")
		{
			std::string tex;
			iss >> tex;
			materials[currentMtl]->setSpecularTex(tex);
		}
		else if (token == "d")
		{
			float dissolve;
			iss >> dissolve;
			materials[currentMtl]->setDissolve(dissolve);
		}
		else if (token == "Ns")
		{
			float Ns;
			iss >> Ns;
			materials[currentMtl]->setNs(Ns);
		}
		else if (token == "map_Kd")
		{
			std::string tex;
			iss >> tex;
			materials[currentMtl]->setDiffuseTex(tex);
		}
		else if (token == "map_Ks")
		{
			std::string tex;
			iss >> tex;
			materials[currentMtl]->setSpecularTex(tex);
		}
	}
	file.close();
	this->mtlData = materials;
	return materials;
}