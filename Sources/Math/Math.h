#pragma once
#include <cmath>
#include "../Constans.h"

namespace Math
{
	static const float64 M_PI = 3.14159265358979323846;
	static const float64 PI = float64(M_PI);
	static const float64 HALF_PI = float64(M_PI)/2.0f;
	static float64 EPSILON  = 0.00000000001f;;
	//static float64 EPSILON  = 0.001f;;

	static bool closeEnough(float64 f1, float64 f2)
	{
		// Determines whether the two float64ing-point values f1 and f2 are
		// close enough together that they can be considered equal.
		return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	}

	static float64 degreesToRadians(float64 degrees)
	{
		return (degrees * PI) / 180.0f;
	}

	static float64 radiansToDegrees(float64 radians)
	{
		return (radians * 180.0f) / PI;
	}
}