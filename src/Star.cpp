#include "Star.h"

#include <iostream>

#include "RenderGL.h"
#include "Math/Math.h"

static const float dist = 20;

Star::Star()
{

}

Star::Star(Vector3 R)
{
	//this->q = q;
	//this->q.normalize();
	this->R = R;
}

Star::~Star()
{

}

void Star::Init()
{
	//Quaternion q = Quaternion(
		//Math::randf(0),
		//Math::randf(0),
		//Math::randf(0),
		//Math::randf(0)
		//);
	//q.normalize();

	//double R = Math::randf(0);	
	//this->q = q;

	this->R = Vector3(Math::randf(0)*dist, Math::randf(0)*dist, Math::randf(0)*dist);

	std::cout << R.x << ": " << R.y << ": " << R.z << " " << std::endl;

	int t = 1;
}

void Star::Draw()
{
 	//Vector3 s = this->q.rotate(Vector3(this->R.x, this->R.y, this->R.z));
	Color4f color = Color4f(Math::randf(0) + 1.0f, Math::randf(0) + 1.0f, Math::randf(0) + 1.0f, Math::randf(0) + 1.0f);
	RenderGL::Instance().DrawSphere(R, rand()%10, color);
}