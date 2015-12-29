#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Color.h"

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

	virtual void Init( const Vector3& Pos_, const Vector3& rand_, const Vector3& w_, const Color4f& color_, unsigned long numParticles_);
	virtual void Draw();

	virtual void applyAcc(Vector3& acc, float dt);
	virtual void simulateForce(float dt);

	void ApplyWind(float dt);
private:
	Entity *E;	
	Vector3 rand;	
	unsigned long numParticles;
};