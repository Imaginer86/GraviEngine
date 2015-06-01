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

void Mass::Set(float m, float r, Vector3 p, Vector3 v, Color4f color)
{
	this->m = m;
	this->r = r;
	this->pos = p;
	this->vel = v;	
	this->color = color;
}

void Mass::Draw()
{
	RenderGL::Instance().DrawSphere(pos, r, color);
}