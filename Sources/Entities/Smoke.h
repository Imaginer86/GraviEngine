#pragma once
#include "Entity.h"
#include "../Math/Vector3d.h"
#include "../Math/Color.h"

class Smoke: public Entity
{
public:
	Smoke();
	virtual ~Smoke();
	void SetRand(const Vector3d& rand_)
	{
		rand = rand_;
	}
	Entity& GetP(unsigned long i)
	{
		return E[i];
	}

	virtual void Init( const Vector3d& pos_, const Vector3d& rand_, const Vector3d& vel0_, const Vector3d& vel_, const Color4f& color_, unsigned long numParticles_, bool createCollision_);
	virtual void Draw();

	virtual void applyAcc(Vector3d& acc, float64 dt);
	virtual void simulateForce(float64 dt);

	void ApplyWind(float64 dt);

	void SetVel0(const Vector3d& vel0_)
	{
		vel0 = vel0_;
	}

	Vector3d GetVel0()
	{
		return vel0;
	}

	unsigned long GetNumParticles()
	{
		return numParticles;
	}

	void SetCreateCollision(bool createCollision_)
	{
		createCollision = createCollision_;
	}

	bool GetCreateCollision()
	{
		return createCollision;
	}
private:
	Entity *E;	
	Vector3d rand;
	Vector3d vel0;
	unsigned long numParticles;
	bool createCollision;
};