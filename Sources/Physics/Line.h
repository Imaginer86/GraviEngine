#pragma once

/*
#include "Entity.h"
#include "../Math/Vector3d.h"
#include "../Math/Quaternion.h"
#include "../Math/Color.h"

class Line: public Entity
{
public:

	Line();

	virtual ~Line(){};

	void SetR(float32 r_)
	{
		this->r = r_;
	}

	virtual float32 GetR()
	{
		return r;
	}

	void SetH(float32 h_)
	{
		this->h = h_;
	}

	virtual float32 GetH()
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

	virtual void applyForce(Vector3d& force_)
	{
		this->force += force_;		
	}

	virtual void simulateForce(float32 dt)
	{
		dt;
	}

	virtual void init()
	{
		
	}	

	virtual bool IsColisions(Entity& entity)
	{
		Vector3d posss = entity.GetPos(); //todo
		return false;
	}

	//virtual float32 ProcessColisions(Entity& entity)
	//{
		//Vector3 pos = entity.GetPos(); //todo
		//return 0.f;
	//}

	virtual void Draw();

private:
	float32 h;
	float32 r;
	Vector3d force;
	Quaternion q;
	Color4f color;
};
*/