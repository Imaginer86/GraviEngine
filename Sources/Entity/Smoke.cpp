#include "Smoke.h"
#include "../Math/Random.h"
#include "../Core/RenderGL.h"

using namespace Math;

void Smoke::Init(float32 m_, const Vector3f& pos_, const Vector3f& rand_, const Vector3f& vel0_, const Vector3f& vel_, const Color4f& color_, unsigned numParticles_, bool createCollision_)
{
	numParticles = numParticles_;
	createCollision = createCollision_;
	E = new Entity[numParticles];
	SetPos(pos_);
	SetVel(vel_);
	SetColor(color_);
	SetMass(m_);
	rand = rand_;
	vel0 = vel0_;
	for ( unsigned i = 0; i < numParticles; ++i)
	{
		
		Vector3f r = Vector3f((Random::Instance().randf() - 0.5f) * 2.0f * rand.x, (Random::Instance().randf() - 0.5f) * 2.0f * rand.y, (Random::Instance().randf() - 0.5f) * 2.0f * rand.z);
		Vector3f posEntity = GetPos() + r;

		bool flag = true;

		for (unsigned j = 0; flag && j < i; ++j)
		{
			Vector3f posEnather = E[j].GetPos();

			Vector3f diff = posEnather - posEntity;
			if (createCollision)
			{

			}
		}
		E[i].SetMass(1.0f);
		Vector3f velll = (GetVel() - vel0);
		velll.x *= (Random::Instance().randf() - 0.5f) * 2.0f;
		velll.y *= (Random::Instance().randf() - 0.5f) * 2.0f;
		velll.z *= (Random::Instance().randf() - 0.5f) * 2.0f;
		E[i].SetVel(velll);
		Color4f col = Color4f(Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf(), Random::Instance().randf());
		E[i].SetColor(col);
	}
}

void Smoke::Draw()
{
	for (unsigned i = 0; i < numParticles; i++)
	{
		Core::RenderGL::Instance().DrawSphere(E[i].GetPos(), 1.0f, E[i].GetColor());
	}
}

void Smoke::applyAcc(Vector3f& acc, float32 dt)
{
	for (unsigned i = 0; i < numParticles; i++)
	{
		SetVel(GetVel() + acc*dt);
	}
	
}


void Smoke::simulateForce(float32 dt)
{
	for (unsigned i = 0; i < numParticles; i++)
	{
		E[i].simulateForce(dt);
	}
}

void Smoke::ApplyWind(float32 dt)
{
	Vector3f windAcc = GetVel();
	applyAcc(windAcc, dt);
}

