#include "Box.h"
#include "../Render/RenderGL.h"

void Box::simulateForce(float32 dt)
{
	Entity::simulateForce(dt);
	Quaternion rotate = qVel;	
	Vector3f axic;
	float32 angle;
	rotate.toAxisAngle(axic, angle);
	angle *= dt;
	rotate.fromAxisAngle(axic, angle);
	q *= rotate;
}

void Box::Draw()
{
	Vector3f axic;
	float32 angle;
	q.toAxisAngle(axic, angle);
	Render::RenderGL::Instance().DrawBox(GetPos(), size, axic, angle, GetColor());
}