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
		Plane(float m_, const Math::Vector2f& size_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Quaternion& q_, const Math::Quaternion& qVel_, const Math::Color4f& color_);
		virtual ~Plane(){};

		virtual void simulateForce(float dt);

		virtual void Draw();

		Math::Vector2f GetSize()
		{
			return size;
		}

		void SetSize(const Math::Vector2f& size_)
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

	protected:
		Math::Vector2f size;
		Math::Quaternion q;
		Math::Quaternion qVel;
	};

	inline Plane::Plane()
	: Entity()
	, size(1.0, 1.0)
	, q(0.0f, 1.0f, 0.0f, 0.0f)
	, qVel(0.0f, 1.0f, 0.0f, 0.0f)
	{
	}

	inline Plane::Plane(float m_, const Math::Vector2f& size_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Quaternion& q_, const Math::Quaternion& qVel_, const Math::Color4f& color_)
	: Entity(m_, pos_, vel_, color_)
	, size(size_)
	, q(q_)
	, qVel(qVel_)
	{
	}

}