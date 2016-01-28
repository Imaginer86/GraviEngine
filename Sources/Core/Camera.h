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

	Vector3f GetView();

	void Interpolate(Quaternion& q_)
	{
		q *= q_;
	}

	void SetPos(Vector3f& pos_)
	{
		pos = pos_;
	}

	Vector3f& GetPos()
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
	Vector3f pos;
	Quaternion q;
};
}