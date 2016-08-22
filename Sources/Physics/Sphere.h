#pragma once
#include "Entity.h"

namespace Physics
{

class Sphere: public Entity
{
	public:	

		Sphere();
		Sphere(float m_, float r_, Math::Vector3f pos_, Math::Vector3f vel_, Math::Color4f color_);								// Constructor	

		virtual ~Sphere(){};	

		void Set(float m_, float r_, Math::Vector3f pos_, Math::Vector3f v_, Math::Color4f color_);

		virtual float GetR()
		{
			return r;
		}

		virtual void Draw();

	protected:
		float r;
	};

	inline Sphere::Sphere()
	: Entity()
	, r(1.0f)
	{

	}


	inline Sphere::Sphere(float m_, float r_, Math::Vector3f pos_, Math::Vector3f vel_, Math::Color4f color_)
	: Entity(m_, pos_, vel_, color_)
	, r(r_)
	{
	}

}