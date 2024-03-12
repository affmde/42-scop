#ifndef MAT4_HPP
# define MAT4_HPP

#include "Vector3f.hpp"

class Mat4
{
public:
	Mat4(float val);
	~Mat4() {}

	Mat4 &operator*=(const Mat4 &other);

	float model[4][4];
	Mat4 translate(Vector3f translateVector);
	Mat4 translate(float x, float y, float z);
	Mat4 scale(Vector3f scaleVector);
	Mat4 scale(float x, float y, float z);
	Mat4 scale(float scale);
	Mat4 rotate(float angle, Vector3f axis);
	void reset();

	void printMatrix();
};

#endif