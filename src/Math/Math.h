#pragma once
//#define  _USE_MATH_DEFINES
#include <ctime>
#include <cmath>





namespace Math
{

	static const float M_PI = 3.14159265358979323846f;

	static const float PI = float(M_PI);
	static const float HALF_PI = float(M_PI)/2.0f;
	//static float EPSILON  = 0.00000000001f;;
	static float EPSILON  = 0.001f;;

	static bool closeEnough(float f1, float f2)
	{
		// Determines whether the two floating-point values f1 and f2 are
		// close enough together that they can be considered equal.

		return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	}

	static float degreesToRadians(float degrees)
	{
		return (degrees * PI) / 180.0f;
	}

	static float radiansToDegrees(float radians)
	{
		return (radians * 180.0f) / PI;
	}

	static float randf(float t)
	{
		return float( rand() / int(RAND_MAX));
	}

	static void randomize()	
	{
		srand(time(NULL));
	}
}