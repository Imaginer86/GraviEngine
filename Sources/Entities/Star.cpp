#include "Star.h"

//#include <iostream>

#include "../Core/RenderGL.h"
#include "../Math/Math.h"

static const float64 dist = 20;

Star::Star()
{

}

Star::Star(Vector3d R_, Quaternion q_)
{
	q = q_;
	q.normalize();
	R = R_;
}

Star::~Star()
{

}

void Star::Init()
{
	//Quaternion q = Quaternion(
		//Math::randf(),
		//Math::randf(),
		//Math::randf(),
		//Math::randf()
		//);
	//q.normalize();

	//double R = Math::randf(0);	
	//this->q = q;

	//this->R = Vector3(Math::randf()*dist, Math::randf()*dist, Math::randf()*dist);

	//std::cout << R.x << ": " << R.y << ": " << R.z << " " << std::endl;
}

void Star::Draw()
{
 	//Vector3 s = this->q.rotate(Vector3(this->R.x, this->R.y, this->R.z));
	//Color4f color = Color4f(Math::randf(), Math::randf() + 1.0f, Math::randf(), Math::randf());	
	//RenderGL::Instance().DrawSphere(R, float64(rand()) / float64(RAND_MAX), color);
}