#pragma once
#include "../Math/Vector3.h"
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

	void RotateUpDown(float64 anglef);

	void RotateLR(float64 angle);

	void MoveCamera(float64 speed);		

	void MoveLRCamera(float64 speed);

	Vector3 GetView();

	void Init()
	{
		pos = Vector3(10.0f, 10.0f, 0.0f);
		q = Quaternion(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void Interpolate(Quaternion& q_)
	{
		q *= q_;
	}

	void SetPos(Vector3& pos_)
	{
		pos = pos_;
	}

	Vector3& GetPos()
	{
		return pos;
	}

	Quaternion GetQuaternion()
	{
		return q;
	}

	void SetQuaternion(Quaternion& q_)
	{
		q = q_;
	}
private:
	Vector3 pos;
	Quaternion q;
};
}