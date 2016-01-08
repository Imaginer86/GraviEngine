#include "sky.h"
#include "../Math/Random.h"
#include "../Core/RenderGL.h"

const float64 dist = 1000;

Sky::Sky()
{

}

Sky::~Sky()
{
	delete[] R;
	delete[] r;
	delete[] color;
}

void Sky::Init(unsigned long numStars_)
{
	numStars = numStars_;
	//Stars = new Star[numStars];
	//return Stars != nullptr;

	R = new Vector3[numStars];
	r = new float64[numStars];
	color = new Color4f[numStars];


	for (unsigned long i = 0; i < this->numStars; i++)
	{
		R[i] = Vector3(dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2), dist * (-1.0f + Random::Instance().randf() * 2));
		r[i] = Random::Instance().randf() * 3.0f;
		color[i] = Color4f(Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf());		
	}
}

void Sky::Randomize()
{
	Random::Instance().randomize();

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
		RenderGL::Instance().DrawSphere(R[i] / 5.0f, r[i], color[i]);
	}
}