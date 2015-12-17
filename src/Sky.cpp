#include "sky.h"
#include "Math/Math.h"
#include "Math/Quaternion.h"

//#include <conio.h>
//#include <stdio.h>
//#include <time.h>

//const double dist = 1000;

Sky::Sky()
{

}

Sky::Sky(long numStars)
{
	this->numStars = numStars;
	Stars = new Star[numStars];


}

Sky::~Sky()
{

}

bool Sky::Init(long numStars)
{
	this->numStars = numStars;
	Stars = new Star[numStars];

	Math::randomize();

	for (long i = 0; i < numStars; ++i)
	{
		Stars[i].Init();
	}
	
	return Stars != nullptr;
}

void Sky::Draw()
{
	for (unsigned long i = 0; i < numStars; ++i)
	{
		Stars[i].Draw();
	}
}