#pragma once
#include "Entity.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"

namespace Physics
{
	class Wave : public Entity
	{
	public:
		Wave();
		Wave(float mass_, unsigned n_, unsigned m_, float size_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Quaternion& q_, const Math::Quaternion& qVel_, const Math::Color4f& color_);
		virtual ~Wave();

		bool initialize();

		virtual void simulateForce(float dt);

		virtual void Draw();

	private:
		static const unsigned sizeN = 32;
		static const unsigned sizeM = 32;
		float wave_movement;										// Our Variable To Move The Waves Across The Mesh
		float mesh[sizeN][sizeM][3];
		Math::Quaternion q;
		Math::Quaternion qVel;
		float size;
	};

	inline Wave::Wave()
		:Entity()
		, wave_movement(0.0f)
		, q(0.0f, 0.0f, 1.0f, 0.0f)
		, qVel(0.0f, 0.0f, 1.0f, 0.0f)
		//, sizeN(32)
		//, sizeM(32)
		, size(1.0f)
	{
	}

	inline Wave::Wave(float mass_, unsigned n_, unsigned m_, float size_, const Math::Vector3f& pos_, const Math::Vector3f& vel_, const Math::Quaternion& q_, const Math::Quaternion& qVel_, const Math::Color4f& color_)
		:Entity(mass_, pos_, vel_, color_)
		, wave_movement(0.0f)
		, q(q_)
		, qVel(qVel_)
		//, sizeN(n_)
		//, sizeM(m_)
		, size(size_)
	{

	}

	inline Wave::~Wave()
	{

	}
}