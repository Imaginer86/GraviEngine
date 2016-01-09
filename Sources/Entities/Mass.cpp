#include "Mass.h"
#include "../Core/RenderGL.h"

using namespace Math;

void Mass::Set(float32 m_, float32 r_, Vector3f pos_, Vector3f vel_, Color4f color_)
{
	r = r_;
	SetPos(pos_);
	SetVel(vel_);
	SetColor(color_);
	SetMass(m_);
}

void Mass::Draw()
{
	Core::RenderGL::Instance().DrawSphere(GetPos(), r, GetColor());
}