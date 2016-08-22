#pragma once
//#include "Mash.h"
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

namespace Physics
{

	class Entity
	{
	public:
		Entity();
		Entity(float m_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Color4f& color_);
		virtual ~Entity(){};

		virtual void init()
		{
			force = Math::Vector3f(0.0f, 0.0f, 0.0f);
		}

		virtual void Draw() {}
	
		virtual void applyForce(const Math::Vector3f& force_)
		{
			this->force += force_;					// The external force is added to the force of the mass
		}

		virtual void applyAcc(Math::Vector3f& acc, float dt) //todo
		{
			vel += acc*dt;
		}

		virtual void simulateForce(float dt)
		{
			if (m != 0.0f)
				vel += (force / m) * dt;				// Change in velocity is added to the velocity.
			// The change is proportinal with the acceleration (force / m) and change in time

			SetPos(GetPos() + vel * dt);						// Change in position is added to the position.
			// Change in position is velocity times the change in time
		}

		float GetMass()
		{
			return m;
		}

		void SetMass(float mass)
		{
			this->m = mass;
		}

		Math::Vector3f GetPos()
		{
			return pos;
		}

		void SetPos(Math::Vector3f pos_)
		{
			this->pos = pos_;
		}

		Math::Vector3f GetVel()
		{
			return vel;
		}

		void SetVel(const Math::Vector3f& v)
		{
			this->vel = v;
		}

		Math::Color4f GetColor()
		{
			return color;
		}

		void SetColor(const Math::Color4f& color_)
		{
			this->color = color_;
		}	

	protected:
		//Mash* Mashes;
		float m;
		Math::Vector3f pos;
		Math::Vector3f vel;
		Math::Vector3f force;
		Math::Color4f color;
	};

	inline Entity::Entity()
	:pos(0.0f, 0.0f, 0.0f)
	,vel(0.0f, 0.0f, 0.0)	
	,force(0.0f, 0.0f, 0.0)
	,color(1.0f, 1.0f, 1.0f, 1.0)
	{
	}

	inline Entity::Entity(float m_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Color4f& color_)
	:pos(pos_)
	,m(m_)
	,vel(vel_)
	,color(color_)
	,force(0.0f, 0.0f, 0.0f)
{}

}