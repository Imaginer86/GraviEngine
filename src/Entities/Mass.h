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
	{}

	Mass(float m, float r, Vector3 pos, Vector3 vel);								// Constructor	

	virtual ~Mass(){};	

	void Set(float m, float r, Vector3 p, Vector3 v, Color4f color);

	virtual void init();

	void simuleteAcc(Vector3 acc, float dt);

	void update(float dt);


	virtual float GetR()
	{
		return r;
	}

	virtual void applyForce(Vector3& force);
	
	virtual void simulateForce(float dt);	

	virtual void Draw();

	virtual void Collision(Entity& entity);
	
	virtual bool IsColisions(Entity& entity)
	{
		Vector3 pos =  entity.GetPos(); //todo
		return false;
	}

	virtual float ProcessColisions(Entity& entity);

private:
	float r;
	Vector3 force;
};
