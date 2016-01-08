#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"

class Smoke: public Entity
{
public:
	Smoke();
	virtual ~Smoke();
	void SetRand(const Vector3& rand_)
	{
		rand = rand_;
	}
	Entity& GetP(unsigned long i)
	{
		return E[i];
	}

	virtual void Init( const Vector3& Pos_, const Vector3& rand_, const Vector3& vel0_, const Vector3& vel_, const Color4f& color_, unsigned long numParticles_, bool createCollision_);
	virtual void Draw();

	virtual void applyAcc(Vector3& acc, float64 dt);
	virtual void simulateForce(float64 dt);

	void ApplyWind(float64 dt);

	void SetVel0(const Vector3& vel0_)
	{
		vel0 = vel0_;
	}

	Vector3 GetVel0()
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
	Vector3 rand;
	Vector3 vel0;
	unsigned long numParticles;
	bool createCollision;
};