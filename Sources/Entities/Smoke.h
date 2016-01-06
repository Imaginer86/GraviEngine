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

	virtual void Init( const Vector3& Pos_, const Vector3& rand_, const Vector3& vel0_, const Vector3& vel_, const Color4f& color_, unsigned long numParticles_);
	virtual void Draw();

	virtual void applyAcc(Vector3& acc, float64 dt);
	virtual void simulateForce(float64 dt);

	void ApplyWind(float64 dt);
private:
	Entity *E;	
	Vector3 rand;
	Vector3 vel0;
	unsigned long numParticles;
};