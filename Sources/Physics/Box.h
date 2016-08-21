﻿#pragma once
#include "Entity.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"

namespace Physics
{

class Box: public Entity
{
public:

	Box();
	Box(float m_, const Math::Vector3f& size_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Quaternion& q_, const Math::Quaternion& qVel_, const Math::Color4f& color_);

	virtual ~Box(){}

	virtual void simulateForce(float dt);

	virtual void Draw();

	Math::Vector3f GetSize()
	{
		return size;
	}

	void SetSize(const Math::Vector3f& size_)
	{
		this->size = size_;
	}

	Math::Quaternion GetAngleQ()
	{
		return q;
	}

	void SetAngleQ(const Math::Quaternion& q_)
	{
		q = q_;
	}

	Math::Quaternion GetAngleVelQ()
	{
		return qVel;
	}

	void SetAngleVelQ(const Math::Quaternion& qVel_)
	{
		qVel = qVel_;
	}

private:	
	Math::Vector3f size;
	Math::Quaternion q;
	Math::Quaternion qVel;
};

inline Box::Box()
: Entity()
, size(1.0, 1.0, 1.0)
, q(0.0f, 1.0f, 0.0f, 0.0f)
, qVel(0.0f, 1.0f, 0.0f, 0.0f)
{
}

inline Box::Box(float m_, const Math::Vector3f& size_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Quaternion& q_, const Math::Quaternion& qVel_, const Math::Color4f& color_)
: Entity(m_, pos_, vel_, color_)
, size(size_)
, q(q_)
, qVel(qVel_)
{
}

}