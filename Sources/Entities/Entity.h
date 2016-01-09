#pragma once
#include "BaseEntity.h"
#include "../Constans.h"
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

class Entity: public BaseEntity
{
public:
	Entity();

	Entity(float32 m_, const Vector3f& pos_, const Vector3f& vel_, const Math::Color4f& color_);

	virtual ~Entity();

	void applyForce(Vector3f& force_)
	{
		this->force += force_;					// The external force is added to the force of the mass
	}

	virtual void applyAcc(Vector3f& acc, float32 dt)
	{
		vel += acc*dt;
	}

	virtual void simulateForce(float32 dt)
	{
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
		// The change is proportinal with the acceleration (force / m) and change in time

		SetPos(GetPos() + vel * dt);						// Change in position is added to the position.
		// Change in position is velocity times the change in time
	}

	virtual void init()
	{
		force = Vector3f(0.0f, 0.0f, 0.0f);
	}

	virtual void Draw() {}

	float32 GetMass()
	{
		return m;
	}

	void SetMass(float32 mass)
	{
		this->m = mass;
	}


	Vector3f GetVel()
	{
		return vel;
	}

	void SetVel(const Vector3f& v)
	{
		this->vel = v;
	}

	Math::Color4f GetColor()
	{
		return color;
	}

	void SetColor(const Math::Color4f& color_)
	{
		this->color = color_;
	}

private:
	float32 m;
	Vector3f vel;
	Vector3f force;
	Math::Color4f color;
};

inline Entity::Entity()
:BaseEntity(Vector3f(0.0, 0.0, 0.0))
,vel(0.0f, 0.0f, 0.0)	
,force(0.0f, 0.0f, 0.0)
,color(1.0f, 1.0f, 1.0f, 1.0)
{
}

inline Entity::Entity(float32 m_, const Vector3f& pos_, const Vector3f& vel_, const Math::Color4f& color_)
:BaseEntity(pos_)
,m(m_)
,vel(vel_)
,color(color_)
,force(0.0f, 0.0f, 0.0f)
{}

inline Entity::~Entity()
{

}