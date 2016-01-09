#pragma once
#include "../Math/Vector3d.h"
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

	Vector3d GetView();

	void Interpolate(Quaternion& q_)
	{
		q *= q_;
	}

	void SetPos(Vector3d& pos_)
	{
		pos = pos_;
	}

	Vector3d& GetPos()
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
	Vector3d pos;
	Quaternion q;
};
}