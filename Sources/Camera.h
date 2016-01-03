#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

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

	void SetPos(Vector3& pos_)
	{
		this->pos = pos_;
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
		this->q = q_;
	}

	void RotateUpDown(float anglef);

	void RotateLR(float angle);

	void MoveCamera(float speed);		

	void MoveLRCamera(float speed);
	
	Vector3 GetView();

private:
	Vector3 pos;
	Quaternion q;
};