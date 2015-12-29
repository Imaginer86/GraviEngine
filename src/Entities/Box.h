#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"

class Box: public Entity
{
public:

	Box();
	virtual ~Box(){};

	Vector3 GetSize()
	{
		return size;
	}

	void SetSize(const Vector3& size_)
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

	virtual void simulateForce(float dt);	

	virtual void Draw();

private:	
	Vector3 size;
	Quaternion q;
	Quaternion qVel;
};