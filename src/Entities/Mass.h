#pragma once

#include "Entity.h"
#include "Box.h"
#include "../Math/Quaternion.h"

#include <typeinfo>

class Mass: public Entity
{
public:	
	Mass()
	: Entity()
	{
	
	}

	virtual ~Mass(){};

	virtual void function()
	{
	}

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

	virtual void Collision(Entity& entity)
	{
		//if (typeid(entity) == typeid(Mass))
		//{
			//Vector3 dp = entity.GetPos() - this->GetPos();
			//float p = Vector3(entity.GetPos() - this->GetPos()).length();
			//float v = (Vector3(entity.GetVel() - this->vel)).length();
			//float dt = (p - entity.GetR() - this->r)/v;

			

		float dt = ProcessColisions(entity);
		if (dt <= 0.0f)
		{
			Vector3 p1 = this->GetPos();
			Vector3 v1 = this->GetVel();			
			Vector3 p2 = entity.GetPos();
			Vector3 v2 = entity.GetVel();

			this->SetPos(p1 + v1*dt);
			entity.SetPos(p2 + v2*dt);

			p1 = this->GetPos();
			p2 = entity.GetPos();

			float m1 = this->GetMass();
			float m2 = entity.GetMass();
			Vector3 p1p2 = p2 - p1;
			Vector3 p2p1 = p1 - p2;
			p1p2.unitize();
			p2p1.unitize();
			Vector3 pn1 = p1p2*v1;
			//pn1.unitize();
			Vector3 v1t = Vector3(p1p2.x*pn1.x*pn1.x + p1p2.x*(pn1.x*pn1.y - pn1.z) + p1p2.x*(pn1.x*pn1.z+pn1.y), 
				p1p2.y*(pn1.y*pn1.x+pn1.z) + p1p2.y*pn1.y*pn1.y + p1p2.y*(pn1.y*pn1.z-pn1.x), 
				p1p2.z*(pn1.z*pn1.x-pn1.y) + p1p2.z*(pn1.z*pn1.y+pn1.x) + p1p2.z*pn1.z*pn1.z);
			float v1n = v1.dotProduct(p1p2);
			float v1ts = v1.dotProduct(v1t);

			//p1p2 = - p1p2;
			Vector3 pn2 = p2p1*v2;
			//pn2.unitize();

			Vector3 v2t = Vector3(p2p1.x*pn2.x*pn2.x + p2p1.x*(pn2.x*pn2.y - pn2.z) + p2p1.x*(pn2.x*pn2.z+pn2.y), 
				p2p1.y*(pn2.y*pn2.x+pn2.z) + p2p1.y*pn2.y*pn2.y + p2p1.y*(pn2.y*pn2.z-pn2.x), 
				p2p1.z*(pn2.z*pn2.x-pn2.y) + p2p1.z*(pn2.z*pn2.y+pn2.x) + p2p1.z*pn2.z*pn2.z);

			float v2n = v2.dotProduct(p2p1);
			float v2ts = v2.dotProduct(v2t);

			//float v1a = - v1n* + ((v1n*m1 + v2n*m2)*2)/(m1 + m2);
			//float v2a = - v2n + ((v1n*m1 + v2n*m2)*2)/(m1 + m2);

			
			Vector3 v11 = p1p2*v1n + ((p1p2*m1*v1n + p2p1*m2*v2n)/(m1+m2))*2.0f;
			Vector3 v22 = v2t - p2p1*v2n + ((p1p2*m1*v1n + p2p1*m2*v2n)/(m1+m2))*2.0f;
			
			this->SetPos(this->GetPos() - this->GetVel()*dt);
			entity.SetPos(entity.GetPos() - entity.GetVel()*dt);

			this->SetVel(-v11);
			entity.SetVel(v22);



			//dt = ProcessColisions(entity);
			//}
			//return dt;
		}
		else if (typeid(entity) == typeid(Box))
		{
			int c = 0;
			//return 0.0f;
		} 
		else
		{
			//return 0.0f;
		}
	}
	
	virtual bool IsColisions(Entity& entity)
	{
		return false;
	}

	virtual float ProcessColisions(Entity& entity)
	{
		if (typeid(entity) == typeid(Mass))
		{
			//Vector3 dp = entity.GetPos() - this->GetPos();
			float p = Vector3(entity.GetPos() - this->GetPos()).length();
			float v = (Vector3(entity.GetVel() - this->vel)).length();
			float dt = (p - entity.GetR() - this->r)/v;

			//if (dt < 0)
				//c++;

			return dt;
		}
		else
		{
			return 0.f;
		}
	}

private:
	float r;
	Vector3 force;
};
