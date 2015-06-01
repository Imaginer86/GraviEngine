#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

class Camera
{
public:
	Camera()
	: pos(0,0,0)
	, Up(0,1,0)
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

	void SetPos(Vector3& pos)
	{
		this->pos = pos;
	}

	Vector3 GetView();

//	void SetView(Vector3 pos2)
//	{
//		this->view = pos2;
//	}

	Vector3 GetUp()
	{
		return Up;
	}

	//void SetUp(Vector3& up)
	//{
		//this->Up = up;
	//}

	Quaternion GetQuaternion()
	{
		return q;
	}

	void SetQuaternion(Quaternion& q)
	{
		this->q = q;
	}
private:
	Vector3 pos;
	Vector3 Up;
	Quaternion q;
};