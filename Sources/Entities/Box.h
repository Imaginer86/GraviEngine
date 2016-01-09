#pragma once
#include "Entity.h"
#include "../Math/Vector3d.h"
#include "../Math/Quaternion.h"

class Box: public Entity
{
public:

	Box();
	virtual ~Box(){};

	virtual void simulateForce(float dt);	

	virtual void Draw();

	Vector3d GetSize()
	{
		return size;
	}

	void SetSize(const Vector3d& size_)
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
	Vector3d size;
	Quaternion q;
	Quaternion qVel;
};