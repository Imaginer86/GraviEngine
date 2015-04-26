#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Color.h"

class Box: public Entity
{
public:

	Box();
	virtual ~Box(){};

	virtual void init();

	Vector3 GetSize()
	{
		return size;
	}

	void SetSize(Vector3 size)
	{
		this->size = size;
	}

	Vector3 GetAngle()
	{
		return angle;
	}

	void SetAngle(Vector3 angle)
	{
		this->angle = angle;
		this->q.fromAngleXYZ(angle);
	}

	Vector3 GetAngleVel()
	{
		return angleVel;
	}

	void SetAngleVel(Vector3 angleVel)
	{
		this->angleVel = angleVel;
		this->qVel.fromAngleXYZ(angleVel);
	}

	virtual void applyForce(Vector3 force)
	{
		return;
	}

	virtual void simulateForce(float dt);	

	virtual void Collision(Entity& Entity)
	{
	}

	virtual bool IsColisions(Entity& Entity)
	{
		return false;
	}

	virtual float ProcessColisions(Entity& entity)
	{
		return 0.0f;
	}

	virtual void Draw();

private:	
	Vector3 size;
	Vector3 angle;
	Vector3 angleVel;
	Vector3 force;
	Quaternion q;
	Quaternion qVel;
};