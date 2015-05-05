#pragma once
#include "../Math/Vector3.h"
#include "../Color.h"

class Entity
{
public:
	Entity()
	: m(1.0f)
	, pos(0.0f, 0.0f, 0.0f)
	, vel(0.0f, 0.0f, 0.0f)
	{
	}

	Entity(float m, Vector3 pos, Vector3 vel, Color4f color)
	: m(m)
	, pos(pos)
	, vel(vel)
	, color(color)
	{}

	virtual ~Entity(){}

	virtual Vector3& GetPos()
	{
		return pos;
	}

	virtual void SetPos(Vector3& pos)
	{
		this->pos = pos;
	}

	virtual Vector3 GetVel()
	{
		return vel;
	}

	virtual void SetVel(Vector3& Vel)
	{
		this->vel = Vel;
	}

	virtual float GetMass()
	{
		return m;
	}

	virtual void SetMass(float& Mass)
	{
		this->m = Mass;
	}

	virtual Color4f GetColor()
	{
		return color;
	}

	void SetColor(Color4f& color)
	{
		this->color = color;
	}

	virtual float GetR()
	{
		return 0.f;
	}

	virtual void applyForce(Vector3& Force) = 0;

	virtual void simulateForce(float dt) = 0;

	virtual void init() = 0;

	virtual void Draw() = 0;

	virtual void Collision(Entity& Entity) = 0;

	virtual bool IsColisions(Entity& Entity) = 0;

	virtual float ProcessColisions(Entity& Entity) = 0;	

public:
	Vector3 pos;
	Vector3 vel;
	float m;
	Color4f color;
};