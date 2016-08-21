#include "Box.h"
#include "../Render/RenderGL.h"

using namespace Physics;
using namespace Math;

void Box::simulateForce(float dt)
{
	Entity::simulateForce(dt);
	Quaternion rotate = qVel;	
	Vector3f axic;
	float angle;
	rotate.toAxisAngle(axic, angle);
	angle *= dt;
	rotate.fromAxisAngle(axic, angle);
	q *= rotate;
}

void Box::Draw()
{
	Vector3f axic;
	float angle;
	q.toAxisAngle(axic, angle);
	Render::RenderGL::Instance().DrawBox(GetPos(), size, axic, angle, GetColor());
}