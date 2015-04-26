#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Color.h"

class Line: public Entity
{
public:

	Line();

	virtual ~Line(){};

	void SetR(float r)
	{
		this->r = r;
	}

	virtual float GetR()
	{
		return r;
	}

	void SetH(float h)
	{
		this->h = h;
	}

	virtual float GetH()
	{
		return h;
	}

	void SetQuaternion(Quaternion q)
	{
		this->q = q;
	}

	Quaternion GetQuaternion()
	{
		return q;
	}

	virtual void applyForce(Vector3 force)
	{
		return;
	}

	virtual void simulateForce(float dt)
	{
		return;
	}

	virtual void init()
	{
		return;
	}	

	virtual void Collision(Entity& Entity)
	{
	}

	virtual bool IsColisions(Entity& Entity)
	{
		return false;
	}

	virtual float ProcessColisions(Entity& entity)
	{
		return 0.f;
	}

	virtual void Draw();

private:
	float h;
	float r;
	Quaternion q;
};

