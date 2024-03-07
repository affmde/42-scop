#ifndef CHECKER_HPP
# define CHECKER_HPP

#include <iostream>

class Checker
{
public:
	Checker(std::string objFile, std::string textureFile);
	~Checker() {}

	bool getIsFileValid() const;
	void check();

private:
	std::string objFile;
	std::string textureFile;
	bool isFileValid;
	
	void fileHasCorrectExtension(std::string expected, std::string actual) const;
	void canOpenFile(std::string file);
	void checkExtension() const;
};

#endif