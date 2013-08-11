#pragma once
#include "vector3D.h"
struct Color4f{
	float r;
	float g;
	float b;
	float a;
};
class Mass
{
public:	
	virtual ~Mass(void);

	double m;
	double r;
	Color4f color;
	Vector3D pos;
	Vector3D vel;
	Vector3D force;
	

	Mass()
	{
	}

	Mass(double m, double r, Vector3D p, Vector3D v)								// Constructor
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


	void Set(double m, double r, Vector3D p, Vector3D v, Color4f color)								// Constructor
	{
		this->m = m;
		this->r = r;
		this->pos = p;
		this->vel = v;
		//this->isLight = isLight;
		this->color = color;
	}

	void applyForce(Vector3D force)
	{
		this->force += force;					// The external force is added to the force of the mass
	}

	void init()
	{
		force.x = 0;
		force.y = 0;
		force.z = 0;
	}

	void simulate(double dt)
	{
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
		// The change is proportinal with the acceleration (force / m) and change in time

		pos += vel * dt;						// Change in position is added to the position.
		// Change in position is velocity times the change in time
	}
};
