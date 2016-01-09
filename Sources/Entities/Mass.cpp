#include "Mass.h"
#include "../Core/RenderGL.h"

Mass::Mass()
: Entity()
, r(0.0f)
{}


Mass::Mass(float64 m_, float64 r_, Vector3d pos_, Vector3d vel_)
: Entity(pos_, m_, vel_, Color4f(0.0f, 0.0f, 0.0f, 0.0f))
, r(r_)
{
}

void Mass::Set(float64 m_, float64 r_, Vector3d pos_, Vector3d vel_, Color4f color_)
{
	m = m_;
	r = r_;
	SetPos(pos_);
	vel = vel_;	
	color = color_;
}

void Mass::Draw()
{
	RenderGL::Instance().DrawSphere(GetPos(), r, color);
}