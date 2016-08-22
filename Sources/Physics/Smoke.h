#pragma once
#include "Entity.h"
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

namespace Physics
{
	class Smoke: public Entity
	{
	public:
		Smoke();
		virtual ~Smoke();
		void SetRand(const Math::Vector3f& rand_)
		{
			rand = rand_;
		}
		Entity& GetP(unsigned i)
		{
			return E[i];
		}

		virtual void Init( float m_, const Math::Vector3f& pos_, const Math::Vector3f& rand_, const Math::Vector3f& vel0_, const Math::Vector3f& vel_, const Math::Color4f& color_, unsigned numParticles_, bool createCollision_);
		virtual void Draw();

		virtual void applyAcc(Math::Vector3f& acc, float dt);
		virtual void simulateForce(float dt);

		void ApplyWind(float dt);

		void SetVel0(const Math::Vector3f& vel0_)
		{
			vel0 = vel0_;
		}

		Math::Vector3f GetVel0()
		{
			return vel0;
		}

		unsigned GetNumParticles()
		{
			return numParticles;
		}

		void SetCreateCollision(bool createCollision_)
		{
			createCollision = createCollision_;
		}

		bool GetCreateCollision()
		{
			return createCollision;
		}
	protected:
		Entity *E;	
		Math::Vector3f rand;
		Math::Vector3f vel0;
		unsigned numParticles;
		bool createCollision;
	};

	inline Smoke::Smoke()
	//:Entity(float m_, Vector3f(0.0f, 0.0f, 0.0f), 1.0f, Vector3f(0.0f, 0.0f, 0.0f), Color4f(1.0f, 1.0f, 1.0f, 1.0f))
	//:E(nullptr)
	//,rand(0.0f, 0.0f, 0.0f)
	//,vel0(0.0f, 0.0f, 0.0f)
	//,numParticles(0),
	//createCollision(false)
	{

	}

	inline Smoke::~Smoke()
	{
		delete[] E;
	}
}