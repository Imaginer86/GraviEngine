#pragma once
#include <cmath>

const float EPSILON = 0.001f;
const float M_PI = 3.14159265358979323846f;   // pi

inline bool closeEnough(float f1, float f2)
{
	return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
}

inline float degreesToRadians(float degrees)
{
	return (degrees * M_PI) / 180.0f;
}

inline float radiansToDegrees(float radians)
{
	return (radians * 180.0f) / M_PI;
}
