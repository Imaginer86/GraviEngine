#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Math/Color.h"

class Line: public Entity
{
public:

	Line();

	virtual ~Line(){};

	void SetR(float r_)
	{
		this->r = r_;
	}

	virtual float GetR()
	{
		return r;
	}

	void SetH(float h_)
	{
		this->h = h_;
	}

	virtual float GetH()
	{
		return h;
	}

	void SetQuaternion(Quaternion q_)
	{
		this->q = q_;
	}

	Quaternion GetQuaternion()
	{
		return q;
	}

	virtual void applyForce(Vector3& force_)
	{
		this->force += force_;		
	}

	virtual void simulateForce(float dt)
	{

	}

	virtual void init()
	{
		
	}	

	virtual bool IsColisions(Entity& entity)
	{
		Vector3 posss = entity.GetPos(); //todo
		return false;
	}

	//virtual float ProcessColisions(Entity& entity)
	//{
		//Vector3 pos = entity.GetPos(); //todo
		//return 0.f;
	//}

	virtual void Draw();

private:
	float h;
	float r;
	Vector3 force;
	Quaternion q;
	Color4f color;
};