#ifndef MTL_PARSER_HPP
# define MTL_PARSER_HPP

#include <string>
#include <unordered_map>

#include "mtl_Material.hpp"

class MtlParser
{
public:
	MtlParser();
	~MtlParser();

	std::unordered_map<std::string, mtl_Material*> parseMtlFile(std::string mtlFile);

private:
	std::unordered_map<std::string, mtl_Material*> mtlData;
};

#endif