#pragma once
#include "BaseEntity.h"
#include "../Math/Vector3.h"
#include "../Color.h"

class Entity: public BaseEntity
{
public:
	Entity();

	Entity(Vector3 pos_, float m_, Vector3 vel_, Color4f color_);

	virtual ~Entity();

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

	virtual Color4f GetColor()
	{
		return color;
	}

	void SetColor(const Color4f& color_)
	{
		this->color = color_;
	}

	void applyForce(Vector3& force_)
	{
		this->force += force_;					// The external force is added to the force of the mass
	}

	virtual void applyAcc(Vector3& acc, float dt)
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

	virtual void Draw() {}

protected:
	float m;
	Vector3 vel;
	Vector3 force;
	Color4f color;
};

inline Entity::Entity()
: BaseEntity(Vector3(0.0f, 0.0f, 0.0f))
, m(1.0f)
, vel(0.0f, 0.0f, 0.0f)	
, force(0.0f, 0.0f, 0.0f)
, color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

inline Entity::Entity(Vector3 pos_, float m_, Vector3 vel_, Color4f color_)
: BaseEntity(pos_)
, m(m_)
, vel(vel_)
, force(0.0f, 0.0f, 0.0f)
{}

inline Entity::~Entity()
{

}