#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Color.h"
class Mass
{
public:	
	Mass(){}
	virtual ~Mass(void){};

	Mass(float m, float r, Vector3 p, Vector3 v)								// Constructor
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

	void applyForce(Vector3 force)
	{
		this->force += force;					// The external force is added to the force of the mass
	}

	void init()
	{
		force.x = 0;
		force.y = 0;
		force.z = 0;
	}

	void simulateForce(float dt)
	{
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
		// The change is proportinal with the acceleration (force / m) and change in time

		pos += vel * dt;						// Change in position is added to the position.
		// Change in position is velocity times the change in time
	}

	void simuleteAcc(Vector3 acc, float dt)
	{
		this->vel += acc * dt;
		
	}

	void update(float dt)
	{
		this->pos += this->vel * dt;
	}


//private:
	float m;
	float r;
	Color4f color;
	Vector3 pos;
	Vector3 vel;
	Vector3 force;
};
