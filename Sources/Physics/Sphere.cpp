#include "Sphere.h"
#include "../Render/RenderGL.h"

using namespace Math;
using namespace Physics;

void Sphere::Set(float m_, float r_, Vector3f pos_, Vector3f vel_, Color4f color_)
{
	r = r_;
	SetPos(pos_);
	SetVel(vel_);
	SetColor(color_);
	SetMass(m_);
}

void Sphere::Draw()
{
	Render::RenderGL::Instance().DrawSphere(GetPos(), r, GetColor());
}