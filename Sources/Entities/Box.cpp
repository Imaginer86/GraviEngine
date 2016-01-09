#include "Box.h"
#include "../Core/RenderGL.h"

Box::Box()
: Entity()
, size(1.0, 1.0, 1.0)
, q(0.0f,0.0f,0.0f,0.0f)
, qVel(0.0f, 0.0f, 0.0f, 0.0f)
{
}

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
	Core::RenderGL::Instance().DrawBox(GetPos(), size, axic, angle, GetColor());
}