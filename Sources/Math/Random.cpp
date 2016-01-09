#include "Random.h"
#include <cstdlib>
#include <ctime>

void Random::randomize()
{
	srand(static_cast<unsigned>(time(NULL)));
}

float32 Random::randf()
{
	return float32(rand()) / float32(RAND_MAX);
}

float32 Random::randfd()
{
	return float32(rand()) / float32(RAND_MAX);
}

float32 Random::randf(float32 a, float32 b)
{
	return float32(rand()) / float32(RAND_MAX) * (b - a) + a;
}


