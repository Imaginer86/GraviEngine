#include "sky.h"
#include "../Math/Random.h"
#include "../Math/Quaternion.h"
#include "../Core/RenderGL.h"

using namespace Math;

const float32 dist = 1000;

Sky::Sky()
{

}

Sky::~Sky()
{

}

void Sky::Init(unsigned numStars_)
{
	numStars = numStars_;
	//Stars = new Star[numStars];
	//return Stars != nullptr;

	RMax = 10000.0f;
	RMin = 9900.0f;
	//RMin = Random::Instance().randf() * 3.0f;
	//RMax = Random::Instance().randf() * 3.0f;		

	Pos = new Vector3f[numStars];
	r = new float32[numStars];
	color = new Color4f[numStars];

	Vector3f n(0.0, 1.0, 0.0);
	float32 dist;
	for (unsigned i = 0; i < this->numStars; i++)
	{
		Vector3f axic = Vector3f(Random::Instance().randf(-1.0f, 1.0f), Random::Instance().randf(-1.0f, 1.0f), Random::Instance().randf(-1.0f, 1.0f));
		axic.unitize();
		float32 angle = 360.0f * Random::Instance().randf();
		Quaternion q;
		q.fromAxisAngle(axic, angle);
		dist = RMin + (RMax - RMin)*Random::Instance().randf();

		
		Pos[i] =  q.rotate(n*dist);
		color[i] = Color4f(Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf());		
		r[i] = Random::Instance().randf()*5.0f;
	}
}

void Sky::Release()
{
	numStars = 0;
	delete[] r;
	delete[] color;
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
	for (unsigned i = 0; i < numStars; ++i)
	{
		//Stars[i].Draw();
		Core::RenderGL::Instance().DrawSphere(Pos[i] / 5.0f, 5.0, color[i]);
	}
}