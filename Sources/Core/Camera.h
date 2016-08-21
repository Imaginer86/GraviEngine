#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"

namespace Core
{
	class Camera
	{
	public:
		Camera();

		virtual  ~Camera();

		static Camera& Instance()
		{
			static Camera SingleCamera;
			return SingleCamera;
		}

		void RotateUpDown(float anglef);

		void RotateLR(float angle);

		void MoveCamera(float speed);		

		void MoveLRCamera(float speed);

		Math::Vector3f GetView();

		void Interpolate(Math::Quaternion& q_)
		{
			q *= q_;
		}

		void SetPos(Math::Vector3f& pos_)
		{
			pos = pos_;
		}

		Math::Vector3f& GetPos()
		{
			return pos;
		}

		Math::Quaternion GetQuaternion()
		{
			return q;
		}

		void SetQuaternion(Math::Quaternion& q_)
		{
			q = q_;
		}
	private:
		Math::Vector3f pos;
		Math::Quaternion q;
	};
}