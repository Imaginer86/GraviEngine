#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

class Camera
{
public:
	Camera()
	: pos(0,0,0)
	, q(0, 1, 1, 1)
	{}
	virtual  ~Camera() {};

	void RotateUpDown(float anglef);

	void RotateLR(float angle);

	void MoveCamera(float speed);		

	void MoveLRCamera(float speed);

	Vector3 GetPos()
	{
		return pos;
	}

	void SetPos(Vector3& pos_)
	{
		this->pos = pos_;
	}

	Vector3 GetView();

//	void SetView(Vector3 pos2)
//	{
//		this->view = pos2;
//	}

	Quaternion GetQuaternion()
	{
		return q;
	}

	void SetQuaternion(Quaternion& q_)
	{
		this->q = q_;
	}
private:
	Vector3 pos;
	Quaternion q;
};