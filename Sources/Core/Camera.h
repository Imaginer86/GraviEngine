#pragma once
#include "../Types.h"
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

	void RotateUpDown(float32 anglef);

	void RotateLR(float32 angle);

	void MoveCamera(float32 speed);		

	void MoveLRCamera(float32 speed);

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