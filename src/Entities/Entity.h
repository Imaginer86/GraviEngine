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
	, force(0.0f, 0.0f, 0.0f)
	{
	}

	Entity(float m, Vector3 pos, Vector3 vel, Color4f color)
	: m(m)
	, pos(pos)
	, vel(vel)
	, force(0.0f, 0.0f, 0.0f)
	{}

	virtual ~Entity(){}

	virtual Vector3 GetPos()
	{
		return pos;
	}

	virtual void SetPos(const Vector3& pos_)
	{
		this->pos = pos_;
	}

	virtual Vector3 GetVel()
	{
		return vel;
	}

	virtual void SetVel(const Vector3& v)
	{
		this->vel = v;
	}

	virtual float GetMass()
	{
		return m;
	}

	virtual void SetMass(const float& mass)
	{
		this->m = mass;
	}

	virtual Color4f GetColor() = 0;

	virtual void SetColor(const Color4f& color) = 0;

	void applyForce(Vector3& force_)
	{
		this->force += force_;					// The external force is added to the force of the mass
	}

	void applyAcc(Vector3& acc, float dt)
	{
		vel += acc*dt;
	}

	virtual void simulateForce(float dt)
	{
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
		// The change is proportinal with the acceleration (force / m) and change in time

		pos += vel * dt;						// Change in position is added to the position.
		// Change in position is velocity times the change in time
	}

	virtual void init()
	{
		force = Vector3(0.0f, 0.0f, 0.0f);
	}

	virtual void Draw() = 0;

protected:
	float m;
	Vector3 pos;
	Vector3 vel;
	Vector3 force;
};