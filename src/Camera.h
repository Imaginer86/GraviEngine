#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

class Camera
{
public:
	Camera()
	: pos(0,0,0)
	//, view(0,0,0)
	, Up(0,1,0)
	//, angle(0,0,0)
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

protected:

	//void AddPosX(float x)
	//{
//		this->pos.x += x;
		//this->view.x += x;
	//}

	//void AddPosY(float y)
	//{
//		this->pos.y += y;
		//this->view.y += y;
	//}

	//void AddPosZ(float z)
	//{
//		this->pos.z += z;
		//this->view.z += z;
	//}

// 	void AddAngleX(float x)
// 	{
// 		this->angle.x += x;
// 		//Quaternion qadd;
// 		//qadd.fromAxisAngle(Vector3(1,0,0), x);
// 		//q += qadd;
// 	}
// 
// 	void AddAngleY(float y)
// 	{
// 		this->angle.y += y;
// 	}
// 
// 	void AddAngleZ(float z)
// 	{
// 		this->angle.z += z;
// 	}

private:
	Vector3 pos;	
	//Vector3 angle;
	Vector3 Up;

	//Vector3 view;
	Quaternion q;
};