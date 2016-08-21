#include "Random.h"
#include <cstdlib>
#include <ctime>

using namespace Math;

void Random::randomize()
{
	srand(static_cast<unsigned>(time(NULL)));
}

float Random::randf()
{
	return float(rand()) / float(RAND_MAX);
}

float Random::randfd()
{
	return float(rand()) / float(RAND_MAX);
}

float Random::randf(float a, float b)
{
	return float(rand()) / float(RAND_MAX) * (b - a) + a;
}


