#pragma once
#include "Entity.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"

class Box: public Entity
{
public:

	Box();
	virtual ~Box(){};

	virtual void simulateForce(float32 dt);	

	virtual void Draw();

	Vector3f GetSize()
	{
		return size;
	}

	void SetSize(const Vector3f& size_)
	{
		this->size = size_;
	}

	Quaternion GetAngleQ()
	{
		return q;
	}

	void SetAngleQ(const Quaternion& q_)
	{
		q = q_;
	}

	Quaternion GetAngleVelQ()
	{
		return qVel;
	}

	void SetAngleVelQ(const Quaternion& qVel_)
	{
		qVel = qVel_;
	}

private:	
	Vector3f size;
	Quaternion q;
	Quaternion qVel;
};