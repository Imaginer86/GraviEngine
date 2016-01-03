#include "Mass.h"
#include "../Core/RenderGL.h"

Mass::Mass()
: Entity()
, r(0.0f)
{}


Mass::Mass(float m_, float r_, Vector3 pos_, Vector3 vel_)
: Entity(pos_, m_, vel_, Color4f(0.0f, 0.0f, 0.0f, 0.0f))
, r(r_)
{
}

void Mass::Set(float m_, float r_, Vector3 pos_, Vector3 vel_, Color4f color_)
{
	m = m_;
	r = r_;
	pos = pos_;
	vel = vel_;	
	color = color_;
}

void Mass::Draw()
{
	RenderGL::Instance().DrawSphere(pos, r, color);
}