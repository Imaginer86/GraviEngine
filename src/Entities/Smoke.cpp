﻿#include "Smoke.h"
#include "../Math/Random.h"
#include "../RenderGL.h"

Smoke::Smoke()
:Entity(0.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Color4f(1.0f, 1.0f, 1.0f, 1.0f))
,E(nullptr)
,rand(0.0f, 0.0f, 0.0f)
,numParticles(0)
{
}

Smoke::~Smoke()
{
	delete[] E;
}

void Smoke::Init( const Vector3& Pos_, const Vector3& rand_, const Vector3& w_, const Color4f& color_, unsigned long numParticles_)
{
	numParticles = numParticles_;
	E = new Entity[numParticles];
	pos = Pos_;
	vel = w_;
	rand = rand_;
	color = color_;
	m = 1.0f;
	for ( unsigned long i = 0; i < numParticles_; i++)
	{
		E[i].SetMass(1.0f);
		Vector3 r = Vector3((Random::Instance().randf() - 0.5f) * 2.0f * rand.x, (Random::Instance().randf() - 0.5f) * 2.0f * rand.y, (Random::Instance().randf() - 0.5f) * 2.0f * rand.z);
		E[i].SetPos(pos + r);		
		Vector3 vel = Vector3((Random::Instance().randf() - 0.5f) * 2.0f * rand.x, (Random::Instance().randf() - 0.5f) * 2.0f * rand.y, (Random::Instance().randf() - 0.5f) * 2.0f * rand.z);
		E[i].SetVel(vel);
		E[i].SetColor(color);		
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
