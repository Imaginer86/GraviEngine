#pragma once

#include "Entity.h"
#include "../Math/Quaternion.h"

class Mass: public Entity
{
public:	
	Mass()
	: Entity()
	{
	
	}

	virtual ~Mass(){};

	Mass(float m, float r, Vector3 p, Vector3 v)								// Constructor
	: Entity()
	{
		this->m = m;
		this->r = r;
		this->pos = p;
		this->vel = v;
		//this->isLight = false;
		this->color.r = 0.0f;
		this->color.g = 0.0f;
		this->color.b = 0.0f;
		this->color.a = 0.0f;
	}


	void Set(float m, float r, Vector3 p, Vector3 v, Color4f color)								// Constructor
	{
		this->m = m;
		this->r = r;
		this->pos = p;
		this->vel = v;
		//this->isLight = isLight;
		this->color = color;
	}

	void simuleteAcc(Vector3 acc, float dt)
	{
		this->vel += acc * dt;
		
	}

	void update(float dt)
	{
		this->pos += this->vel * dt;
	}

	Color4f GetColor()
	{
		return color;
	}

	virtual float GetR()
	{
		return r;
	}

	virtual void applyForce(Vector3 force)
	{
		this->force += force;					// The external force is added to the force of the mass
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
		force.x = 0;
		force.y = 0;
		force.z = 0;
	}

	virtual void Draw();

private:
	float r;
	Vector3 force;
};
