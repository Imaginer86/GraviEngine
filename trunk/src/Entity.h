#pragma once
#include "Vector3.h"

class Entity
{
public:
	Entity():m(1.0f), pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f)
	{

	}
	Vector3 GetPos()
	{
		return pos;
	}

	void SetPos(Vector3 pos)
	{
		this->pos = pos;
	}

	Vector3 GetVel()
	{
		return vel;
	}

	float GetMass()
	{
		return m;
	}

	void SetMass(float mass)
	{
		this->m = mass;
	}
protected:
	Vector3 pos;
	Vector3 vel;
	float m;
};