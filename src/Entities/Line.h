﻿#pragma once
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

	virtual void applyForce(Vector3& force)
	{
		this->force += force;
		return;
	}

	virtual void simulateForce(float dt)
	{
		float t = dt; // todo
		t++;
		return;
	}

	virtual void init()
	{
		return;
	}	

	virtual void Collision(Entity& entity)
	{
		Vector3 pos = entity.GetPos(); //todo
	}

	virtual bool IsColisions(Entity& entity)
	{
		Vector3 pos = entity.GetPos(); //todo
		return false;
	}

	virtual float ProcessColisions(Entity& entity)
	{
		Vector3 pos = entity.GetPos(); //todo
		return 0.f;
	}

	virtual void Draw();

private:
	float h;
	float r;
	Vector3 force;
	Quaternion q;
};
