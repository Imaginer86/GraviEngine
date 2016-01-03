#include "Random.h"
#include <cstdlib>
#include <ctime>

float Random::randf()
{
	return float(rand()) / float(RAND_MAX);
}

void Random::randomize()
{
	srand(static_cast<unsigned int>(time(NULL)));
}
