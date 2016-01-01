﻿#pragma once
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

	void RotateUpDown(float anglef);

	void RotateLR(float angle);

	void MoveCamera(float speed);		

	void MoveLRCamera(float speed);

	void SetPos(Vector3& pos_)
	{
		this->pos = pos_;
	}

	Vector3& GetPos()
	{
		return pos;
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