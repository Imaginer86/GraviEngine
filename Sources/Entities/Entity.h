#pragma once
#include "BaseEntity.h"
#include "../Constans.h"
#include "../Math/Vector3d.h"
#include "../Math/Color.h"

class Entity: public BaseEntity
{
public:
	Entity();

	Entity(Vector3d pos_, float64 m_, Vector3d vel_, Color4f color_);

	virtual ~Entity();

	Vector3d GetVel()
	{
		return vel;
	}

	void SetVel(const Vector3d& v)
	{
		this->vel = v;
	}

	float64 GetMass()
	{
		return m;
	}

	void SetMass(const float64& mass)
	{
		this->m = mass;
	}

	Color4f GetColor()
	{
		return color;
	}

	void SetColor(const Color4f& color_)
	{
		this->color = color_;
	}

	void applyForce(Vector3d& force_)
	{
		this->force += force_;					// The external force is added to the force of the mass
	}

	virtual void applyAcc(Vector3d& acc, float64 dt)
	{
		vel += acc*dt;
	}

	virtual void simulateForce(float64 dt)
	{
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
		// The change is proportinal with the acceleration (force / m) and change in time

		SetPos(GetPos() + vel * dt);						// Change in position is added to the position.
		// Change in position is velocity times the change in time
	}

	virtual void init()
	{
		force = Vector3d(0.0f, 0.0f, 0.0f);
	}

	virtual void Draw() {}

protected:
	float64 m;
	Vector3d vel;
	Vector3d force;
	Color4f color;
};

inline Entity::Entity()
: BaseEntity(Vector3d(0.0, 0.0, 0.0))
, m(1.0)
, vel(0.0f, 0.0f, 0.0)	
, force(0.0f, 0.0f, 0.0)
, color(1.0f, 1.0f, 1.0f, 1.0)
{
}

inline Entity::Entity(Vector3d pos_, float64 m_, Vector3d vel_, Color4f color_)
: BaseEntity(pos_)
, m(m_)
, vel(vel_)
, force(0.0f, 0.0f, 0.0f)
{}

inline Entity::~Entity()
{

}