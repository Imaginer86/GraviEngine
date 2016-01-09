#pragma once
#include <cmath>
#include "../Constans.h"

namespace Math
{
	const float64 M_PI = 3.14159265358979323846;
	const float64 HALF_PI = M_PI/2.0;
	const float64 EPSILON  = 0.00000000001;
	

	inline bool closeEnough(float64 f1, float64 f2)
	{
		// Determines whether the two float64ing-point values f1 and f2 are
		// close enough together that they can be considered equal.
		return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	}

	inline unsigned Max(unsigned f1, unsigned f2)
	{
		// Determines whether the two float64ing-point values f1 and f2 are
		// close enough together that they can be considered equal.
		return f1 > f2 ? f1 : f2;
	}

	inline float64 degreesToRadians(float64 degrees)
	{
		return (degrees * M_PI) / 180.0f;
	}

	inline float64 radiansToDegrees(float64 radians)
	{
		return (radians * 180.0f) / M_PI;
	}
}