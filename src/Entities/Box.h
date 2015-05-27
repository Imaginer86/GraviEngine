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

	Vector3 GetSize()
	{
		return size;
	}

	void SetSize(Vector3& size)
	{
		this->size = size;
	}

	Quaternion GetAngleQ()
	{
		return q;
	}

	void SetAngleQ(Quaternion q_)
	{
		q = q_;
	}

	Quaternion GetAngleVelQ()
	{
		return qVel;
	}

	void SetAngleVelQ(Quaternion qVel_)
	{
		qVel = qVel_;
	}

	virtual Color4f GetColor()
	{
		return color;
	}

	void SetColor(Color4f& color)
	{
		this->color = color;
	}


	virtual void simulateForce(float dt);	

	virtual void Draw();

private:	
	Vector3 size;
	Quaternion q;
	Quaternion qVel;
	Color4f color;
};