#include "Box.h"
#include "..\RenderGL.h"

Box::Box()
: Entity()
, size(1.0, 1.0, 1.0)
, q(0.0f,0.0f,0.0f,0.0f)
, qVel(0.0f, 0.0f, 0.0f, 0.0f)
{
}

void Box::simulateForce(float dt)
{
	Entity::simulateForce(dt);
	Quaternion rotate = qVel;	
	Vector3 axic;
	float angle;
	rotate.toAxisAngle(axic, angle);
	angle *= dt;
	rotate.fromAxisAngle(axic, angle);
	q *= rotate;
}

void Box::Draw()
{
	Vector3 axic;
	float angle;
	q.toAxisAngle(axic, angle);
	RenderGL::Instance().DrawBox(pos, size, axic, angle, color);
}