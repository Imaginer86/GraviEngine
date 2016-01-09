#include "Random.h"
#include <cstdlib>
#include <ctime>

void Random::randomize()
{
	srand(static_cast<unsigned int>(time(NULL)));
}

float32 Random::randf()
{
	return float(rand()) / float(RAND_MAX);
}

float64 Random::randfd()
{
	return float64(rand()) / float64(RAND_MAX);
}

float32 Random::randf(float32 a, float32 b)
{
	return float(rand()) / float(RAND_MAX) * (b - a) + a;
}


