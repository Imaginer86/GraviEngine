#include "sky.h"
//#include <iostream>
#include "Color.h"
#include "RenderGL.h"
#include "Math/Random.h"
//#include "Math/Math.h"
//#include "Math/Quaternion.h"

//#include <conio.h>
//#include <stdio.h>
//#include <time.h>

const float dist = 1000;

//#include <cstdlib>
//#include <ctime>

Sky::Sky()
{

}

Sky::Sky(long numStars_)
{
	numStars = numStars_;
	//Stars = new Star[numStars];
}

Sky::~Sky()
{

}

void Sky::Init(unsigned long numStars_)
{
	numStars = numStars_;
	//Stars = new Star[numStars];
	//return Stars != nullptr;

	this->q = new Quaternion[numStars];
	this->R = new Vector3[numStars];

	for (unsigned long i = 0; i < this->numStars; i++)
	{
		q[i].fromAxisAngle(Vector3(dist * (-1.0f + Random::Instance().randf() * 2) , dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2)),
			360.0f * Random::Instance().randf() * 2);
		q[i].normalize();
		R[i] = Vector3(dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2));

		//std::cout << R[i].x << " " << R[i].y << " " << R[i].z << " " << std::endl;
	}
}

void Sky::Randomize()
{
	Random::Instance().randomize();
	//Math::randomize();

	//for (long i = 0; i < numStars; ++i)
	//{
		//Stars[i].Init();
	//}
}

void Sky::Draw()
{
	for (unsigned long i = 0; i < numStars; ++i)
	{
		//Stars[i].Draw();
		//Color4f color = Color4f(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX));
		Color4f color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
		RenderGL::Instance().DrawSphere(R[i] / 10.0f, 10.0f, color);
	}
}