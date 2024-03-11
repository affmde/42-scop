#include "Mat4.hpp"

#include <iostream>
#include <strings.h>
#include <cmath>

Mat4::Mat4(float val)
{
	bzero(&this->model, sizeof(this->model));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				this->model[i][j] = val;
		}
	}
}

Mat4 Mat4::translate(Vector3f translateVector)
{
	Mat4 newMat(1.0f);

	newMat.model[0][3] = translateVector.getX();
	newMat.model[1][3] = translateVector.getY();
	newMat.model[2][3] = translateVector.getZ();
	return newMat;
}
Mat4 Mat4::translate(float x, float y, float z)
{
	Mat4 newMat(1.0f);

	newMat.model[0][3] = x;
	newMat.model[1][3] = y;
	newMat.model[2][3] = z;
	return newMat;
}

Mat4 Mat4::scale(Vector3f scaleVector)
{
	Mat4 newMat(1.0f);

	newMat.model[0][0] = scaleVector.getX();
	newMat.model[1][1] = scaleVector.getY();
	newMat.model[2][2] = scaleVector.getZ();
	return newMat;
}
Mat4 Mat4::scale(float x, float y, float z)
{
	Mat4 newMat(1.0f);

	newMat.model[0][0] = x;
	newMat.model[1][1] = y;
	newMat.model[2][2] = z;
	return newMat;
}
Mat4 Mat4::scale(float scale)
{
	Mat4 newMat(1.0f);

	newMat.model[0][0] = scale;
	newMat.model[1][1] = scale;
	newMat.model[2][2] = scale;
	return newMat;
}

Mat4 Mat4::rotate(float angle, Vector3f axis)
{
	Mat4 newMat(1.0f);

	float c = cos(angle);
	float s = sin(angle);
	float t = 1 - c;

	float x = axis.getX();
	float y = axis.getY();
	float z = axis.getZ();

	newMat.model[0][0] = t * x * x + c;
	newMat.model[0][1] = t * x * y - s * z;
	newMat.model[0][2] = t * x * z + s * y;

	newMat.model[1][0] = t * x * y + s * z;
	newMat.model[1][1] = t * y * y + c;
	newMat.model[1][2] = t * y * z - s * x;

	newMat.model[2][0] = t * x * z - s * y;
	newMat.model[2][1] = t * y * z + s * x;
	newMat.model[2][2] = t * z * z + c;

	return newMat;
}

void Mat4::reset()
{
	bzero(&this->model, sizeof(this->model));
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if (i == j)
				this->model[i][i] = 1.0f;
		}
	}
}

void Mat4::printMatrix()
{
	std::cout << "Matrix: " << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "| ";
		for (int j = 0; j < 4; j++)
		{
			std::cout << this->model[i][j] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

Mat4 &Mat4::operator*=(const Mat4 &other)
{
	Mat4 newMat(1.0f);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newMat.model[i][j] = this->model[i][0] * other.model[0][j] +
								 this->model[i][1] * other.model[1][j] +
								 this->model[i][2] * other.model[2][j] +
								 this->model[i][3] * other.model[3][j];
		}
	}
	*this = newMat;
	return *this;
}