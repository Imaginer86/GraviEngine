#pragma once
#include "../Math/Vector3.h"
#include "../Color.h"

class Entity
{
public:
	Entity():m(1.0f), pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f)
	{

	}

	virtual ~Entity(){}

	virtual Vector3 GetPos()
	{
		return pos;
	}

	virtual void SetPos(Vector3 pos)
	{
		this->pos = pos;
	}

	virtual Vector3 GetVel()
	{
		return vel;
	}

	virtual void SetVel(Vector3 vel)
	{
		this->vel = vel;
	}

	virtual float GetMass()
	{
		return m;
	}

	virtual void SetMass(float mass)
	{
		this->m = mass;
	}

	virtual Color4f GetColor()
	{
		return color;
	}

	virtual float GetR() = 0;

	virtual void applyForce(Vector3 force) = 0;

	virtual void simulateForce(float dt) = 0;

	virtual void init() = 0;

	virtual void Draw() = 0;

protected:
	Vector3 pos;
	Vector3 vel;
	float m;
	Color4f color;
};