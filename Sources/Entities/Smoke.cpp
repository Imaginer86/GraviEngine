#include "Smoke.h"
#include "../Math/Random.h"
#include "../Core/RenderGL.h"

Smoke::Smoke()
:Entity(Vector3(0.0f, 0.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f), Color4f(1.0f, 1.0f, 1.0f, 1.0f))
//,E(nullptr)
,rand(0.0f, 0.0f, 0.0f)
,numParticles(0)
{
}

Smoke::~Smoke()
{
	delete[] E;
}

void Smoke::Init( const Vector3& Pos_, const Vector3& rand_, const Vector3& vel0_, const Vector3& vel_, const Color4f& color_, unsigned long numParticles_)
{
	numParticles = numParticles_;
	E = new Entity[numParticles];
	pos = Pos_;
	rand = rand_;
	vel0 = vel0_;
	vel = vel_;	
	color = color_;
	m = 1.0f;
	for ( unsigned long i = 0; i < numParticles_; i++)
	{
		E[i].SetMass(1.0f);
		Vector3 r = Vector3((Random::Instance().randf() - 0.5f) * 2.0f * rand.x, (Random::Instance().randf() - 0.5f) * 2.0f * rand.y, (Random::Instance().randf() - 0.5f) * 2.0f * rand.z);
		E[i].SetPos(pos + r);		
		Vector3 velll = (vel - vel0);
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
	for (unsigned long i = 0; i < numParticles; i++)
	{
		RenderGL::Instance().DrawSphere(E[i].GetPos(), 1.0f, E[i].GetColor());
	}
}

void Smoke::applyAcc(Vector3& acc, float dt)
{
	for (unsigned long i = 0; i < numParticles; i++)
	{
		vel += acc*dt;
	}
	
}


void Smoke::simulateForce(float dt)
{
	for (unsigned long i = 0; i < numParticles; i++)
	{
		E[i].simulateForce(dt);
	}
}

void Smoke::ApplyWind(float dt)
{
	applyAcc(vel, dt);
}

