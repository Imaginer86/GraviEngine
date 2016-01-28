#pragma once

#include "Entity.h"
#include "../Math/Vector2f.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"

namespace Physics
{
class Plane: public Entity
{
public:
	Plane();
	Plane(float m_, const Vector2f& size_, const Vector3f& pos_, const Vector3f& vel_, const Quaternion& q_, const Quaternion& qVel_, const Math::Color4f& color_);
	virtual ~Plane(){};

	virtual void simulateForce(float dt);

	virtual void Draw();

	Vector2f GetSize()
	{
		return size;
	}

	void SetSize(const Vector2f& size_)
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
	Vector2f size;
	Quaternion q;
	Quaternion qVel;
};

inline Plane::Plane()
: Entity()
, size(1.0, 1.0)
, q(0.0f, 1.0f, 0.0f, 0.0f)
, qVel(0.0f, 1.0f, 0.0f, 0.0f)
{
}

inline Plane::Plane(float m_, const Vector2f& size_, const Vector3f& pos_, const Vector3f& vel_, const Quaternion& q_, const Quaternion& qVel_, const Math::Color4f& color_)
: Entity(m_, pos_, vel_, color_)
, size(size_)
, q(q_)
, qVel(qVel_)
{
}

}