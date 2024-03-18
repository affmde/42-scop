#ifndef BMP_HPP
# define BMP_HPP

#include <string>
#include <vector>
typedef struct s_Color
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}	t_color;
typedef struct s_image
{
	int height;
	int width;
	t_color **rgb;
}	t_image;
typedef struct s_BMPHeader
{
	char name[2];
	unsigned int fileSize;
	int garbage;
	unsigned int offset;
}	t_BMPHeader;
typedef struct s_BMPInfo
{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short int planes;
	unsigned short int bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int temp[4];
}	t_BMPinfo;

class BMP
{
public:
	BMP(std::string fileName);
	~BMP();

	unsigned char *getData();
	int getWidth() const { return this->img.width; }
	int getHeight() const { return this->img.height; }

private:
	std::string filePath;

	t_BMPHeader header;
	t_BMPinfo info;

	t_image img;
	unsigned char *imgData;

	void readFile();
	unsigned char greyScale(t_color rgb);
	void convertImageToGrayScale();
	int createBlackAndWhiteImage(t_BMPHeader header, t_BMPinfo info);
	void convertData();

};

#endif