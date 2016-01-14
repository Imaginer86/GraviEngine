#pragma once
#include "Entity.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"

class Box: public Entity
{
public:

	Box();
	Box(float32 m_, const Vector3f& size_, const Vector3f& pos_, const Vector3f& vel_, const Quaternion& q_, const Quaternion qVel_, Math::Color4f color_);

	virtual ~Box();

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

inline Box::Box()
: Entity()
, size(1.0, 1.0, 1.0)
, q(0.0f, 1.0f, 0.0f, 0.0f)
, qVel(0.0f, 1.0f, 0.0f, 0.0f)
{
}

inline Box::Box(float32 m_, const Vector3f& size_, const Vector3f& pos_, const Vector3f& vel_, const Quaternion& q_, const Quaternion qVel_, Math::Color4f color_)
: Entity(m_, pos_, vel_, color_)
, size(size_)
, q(q_)
, qVel(qVel_)
{
}

inline Box::~Box()
{
}