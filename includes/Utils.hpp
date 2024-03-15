#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <vector>

#include "Vector3f.hpp"
#include "Mat4.hpp"

std::vector<std::string> str_split(std::string string, std::string delimeter);
float toRadians(int deg);
float dot(const Vector3f &a, const Vector3f &b);
Mat4 lookAt(const Vector3f &camPosition, const Vector3f &targetPosition, Vector3f worldUp);
Mat4 perspective(float fov, float aspect, float near, float far);
Vector3f cross(const Vector3f &a, const Vector3f &b);
Vector3f normalize(const Vector3f &a);
Vector3f getRandomColor();

#endif