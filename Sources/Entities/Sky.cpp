#include "sky.h"
//#include <iostream>
#include "../Math/Color.h"
#include "../Math/Random.h"
#include "../Core/RenderGL.h"


const float64 dist = 1000;

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
	//delete[] q;
	delete[] R;
	delete[] r;
}

void Sky::Init(unsigned long numStars_)
{
	numStars = numStars_;
	//Stars = new Star[numStars];
	//return Stars != nullptr;

	//q = new Quaternion[numStars];
	R = new Vector3[numStars];
	r = new float64[numStars];


	for (unsigned long i = 0; i < this->numStars; i++)
	{
		//q[i].fromAxisAngle(Vector3(dist * (-1.0f + Random::Instance().randf() * 2) , dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2)),
			//360.0f * Random::Instance().randf() * 2);
		//q[i].normalize();
		R[i] = Vector3(dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2));
		r[i] = Random::Instance().randf() * 3.0f;

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
		//Color4f color = Color4f(float64(rand()) / float64(RAND_MAX), float64(rand()) / float64(RAND_MAX), float64(rand()) / float64(RAND_MAX), float64(rand()) / float64(RAND_MAX));
		Color4f color = Color4f(Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf(), 1.0);
		RenderGL::Instance().DrawSphere(R[i] / 5.0f, r[i], color);
	}
}