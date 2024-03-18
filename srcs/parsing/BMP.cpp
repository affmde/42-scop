#include <fstream>
#include <iostream>
#include <string.h>

#include "BMP.hpp"

BMP::BMP(std::string fileName)
{
	this->filePath = fileName;
	bzero(&this->header.name, sizeof(this->header.name));
	this->header.fileSize = 0;
	this->header.garbage = 0;
	this->header.offset = 0;

	this->info.headerSize = 0;
	this->info.width = 0;
	this->info.height = 0;
	this->info.planes = 1;
	this->info.bitsPerPixel = 0;
	this->info.compression = 0;
	this->info.imageSize = 0;


	this->colorHeader.redMask = 0x00FF0000;
	this->colorHeader.greenMask = 0x0000FF00;
	this->colorHeader.blueMask = 0x000000FF;
	this->colorHeader.alphaMask = 0xFF000000;
	this->colorHeader.colorSpaceType = 0x73524742;
	bzero(this->colorHeader.unused, sizeof(this->colorHeader.unused));

	this->readFile();
}
BMP::~BMP()
{
	for(int i = 0; i < this->img.height; i++)
		delete[] this->img.rgb[i];
	delete[] this->img.rgb;
	delete[] this->imgData;
}

void BMP::convertData() 
{
	this->imgData = new unsigned char[this->img.width * this->img.height * 3]; // 3 components (R, G, B)

    for (int y = 0; y < this->img.height; ++y) {
        for (int x = 0; x < this->img.width; ++x) {
            int pixelIndex = (y * this->img.width + x) * 3; // index for the pixel in imageData

            this->imgData[pixelIndex + 0] = this->img.rgb[y][x].r; // Red component
            this->imgData[pixelIndex + 1] = this->img.rgb[y][x].g; // Green component
            this->imgData[pixelIndex + 2] = this->img.rgb[y][x].b; // Blue component
        }
    }
}

unsigned char *BMP::getData() { return this->imgData; }

void BMP::readFile()
{
	FILE * file = fopen(this->filePath.c_str(), "rb");
	if (!file)
		throw std::runtime_error("Failed to open the file " + this->filePath);
	fread(this->header.name, sizeof(char) * 2, 1, file);
	
	if (this->header.name[0] != 'B' || this->header.name[1] != 'M')
	{
		fclose(file);
		throw std::runtime_error("The file is not a BMP file. Header is not 0x4D42");
	}
	fread(&this->header.fileSize, sizeof(int) * 3, 1, file);
	fread(&this->info, sizeof(t_BMPinfo), 1, file);

	if (this->info.headerSize != 40)
	{
		fclose(file);
		throw std::runtime_error("Program does not handle bmp files with color header");
	}
	if (this->info.compression != 0)
	{
		fclose(file);
		throw std::runtime_error("Program does not handle compressed files. Try another file");
	}

	fseek(file, this->header.offset, SEEK_SET);

	this->img.height = this->info.height;
	this->img.width = this->info.width;
	int bytesToread = ((24 * this->info.width + 31) / 32) * 4;
	int nbrOfRGB = bytesToread / sizeof(t_color) + 1;
	
	this->img.rgb = new t_color*[this->info.height];
	for (int i = this->img.height - 1; i >= 0; i--)
	{
		this->img.rgb[i] = new t_color[this->info.width];
		fread(this->img.rgb[i], 1, bytesToread, file);
	}
	fclose(file);
	this->convertData();
}

unsigned char BMP::greyScale(t_color rgb)
{
	return ((0.3f * rgb.r) + (0.6f * rgb.g) + (0.1f * rgb.b));
}

void BMP::convertImageToGrayScale()
{
	for(int i = 0; i < this->img.height; i++)
	{
		for (int j = 0; j < this->img.width; j++)
		{
			unsigned char grey = this->greyScale(this->img.rgb[i][j]);
			this->img.rgb[i][j].r = grey;
			this->img.rgb[i][j].g = grey;
			this->img.rgb[i][j].b = grey;
		}
	}
}

int BMP::createBlackAndWhiteImage(t_BMPHeader header, t_BMPinfo info, t_BMPColorHeader colorHeader)
{
	FILE *file = fopen((this->filePath + "bw.bmp").c_str(), "wb");
	if (!file)
		throw std::runtime_error("Failed to create the file blackAndWhite.bmp");
	
	fwrite(header.name, sizeof(char) * 2, 1, file);
	fwrite(&header.fileSize, 3 * sizeof(int), 1, file);

	fwrite(&info, sizeof(t_BMPinfo), 1, file);

	this->convertImageToGrayScale();

	int bytesToread = ((24 * this->info.width + 31) / 32) * 4;
	for (int i = this->img.height - 1; i >= 0; i--)
		fwrite(this->img.rgb[i], bytesToread, 1, file);
	fclose(file);
	return 0;
}