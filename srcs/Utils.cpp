#include "Utils.hpp"

std::vector<std::string> str_split(std::string line, std::string delimeter)
{
	std::vector<std::string> vector;
	size_t pos = 0;
	std::string token;
	while((pos = line.find(delimeter)) != std::string::npos)
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimeter.length());
		vector.push_back(token);
	}
	if (!line.empty())
		vector.push_back(line);
	return vector;
}