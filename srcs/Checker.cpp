#include <fstream>

#include "Checker.hpp"

Checker::Checker(std::string objFile, std::string textureFile)
{
	this->objFile = objFile;
	this->textureFile = textureFile;
	this->isFileValid = false;
}

bool Checker::getIsFileValid() const { return this->isFileValid; }

void Checker::check()
{
	this->checkExtension();
	this->canOpenFile(this->objFile);
	//this->canOpenFile(this->textureFile);
};

void Checker::fileHasCorrectExtension(std::string expected, std::string actual) const
{
	size_t dotIndex = actual.find_last_of(".");
	std::string actualExtension;
	if (dotIndex == std::string::npos)
		throw std::runtime_error(actual + " has wrong extension");
	actualExtension = actual.substr(dotIndex);
	if (!expected.compare(actualExtension) == 0)
		throw std::runtime_error(actual + " has wrong extension");
}

void Checker::checkExtension() const
{
	this->fileHasCorrectExtension(".obj", this->objFile);
	//this->fileHasCorrectExtension(".mtl", this->textureFile);
}

void Checker::canOpenFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
		file.close();
	else
		throw std::runtime_error("Failed to open " + fileName);
}
