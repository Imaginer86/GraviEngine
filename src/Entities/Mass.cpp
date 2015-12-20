#include "Mass.h"
#include "..\RenderGL.h"

Mass::Mass()
: Entity()
, r(0.0f)
, color(1.0f, 1.0f, 1.0f, 1.0f)
{}


Mass::Mass(float m_, float r_, Vector3 pos_, Vector3 vel_)
: Entity(m_, pos_, vel_, Color4f(0.0f, 0.0f, 0.0f, 0.0f))
, r(r_)
{
}

void Mass::Set(float m_, float r_, Vector3 p_, Vector3 vel_, Color4f color_)
{
	this->m = m_;
	this->r = r_;
	this->pos = p_;
	this->vel = vel_;	
	this->color = color_;
}

void Mass::Draw()
{
	RenderGL::Instance().DrawSphere(pos, r, color);
}