#pragma once
#include "../Math/Vector3.h"
#include "../Color.h"

class Entity
{
public:
	Entity():m(1.0f), pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f), c(0)
	{

	}

	virtual ~Entity(){}

	virtual void function() = 0;

	virtual Vector3& GetPos()
	{
		return pos;
	}

	virtual void SetPos(Vector3 Pos)
	{
		this->pos = pos;
	}

	virtual Vector3 GetVel()
	{
		return vel;
	}

	virtual void SetVel(Vector3 Vel)
	{
		this->vel = Vel;
	}

	virtual float GetMass()
	{
		return m;
	}

	virtual void SetMass(float Mass)
	{
		this->m = Mass;
	}

	virtual Color4f GetColor()
	{
		return color;
	}

	virtual float GetR()
	{
		return 0.f;
	}

	virtual void applyForce(Vector3 Force)
	{
	}

	virtual void simulateForce(float dt)
	{
	}

	virtual void init()
	{
	}

	virtual void Draw() = 0;

	virtual void Collision(Entity& Entity)
	{
	}

	virtual bool IsColisions(Entity& Entity)
	{
		return false;
	}

	virtual float ProcessColisions(Entity& Entity) = 0;	

public:
	Vector3 pos;
	Vector3 vel;
	float m;
	Color4f color;
	unsigned int c;
};