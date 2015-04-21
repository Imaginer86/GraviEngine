#pragma once
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"

class Camera
{
public:
	Camera():pos(0,0,0), view(0,0,0), Up(0,1,0)//, angle(0,0,0)
	{}
	virtual  ~Camera() {};

	Vector3 GetPos()
	{
		return pos;
	}

	void SetPos(Vector3 pos)
	{
		this->pos = pos;
	}

	Vector3 GetView()
	{
		return view;
	}

	void SetView(Vector3 pos2)
	{
		this->view = pos2;
	}

	Vector3 GetUp()
	{
		return Up;
	}

	void SetUp(Vector3 up)
	{
		this->Up = up;
	}

	void AddPosX(float x)
	{
		this->pos.x += x;
		this->view.x += x;
	}

	void AddPosY(float y)
	{
		this->pos.y += y;
		this->view.y += y;
	}

	void AddPosZ(float z)
	{
		this->pos.z += z;
		this->view.z += z;
	}

	void RotateView(float angle)
	{
		Vector3 v;
		v = view - pos;
		view.z = pos.z + sin(angle) * v.x + cos(angle) * v.z;
		view.x = pos.x + cos(angle) * v.x - sin(angle) * v.z;
	}

	void MoveCamera(float speed)
	{
		Vector3 v;
		v = view - pos;

		v.y = 0;
		v.unitize();

		pos += v*speed;
		view += v*speed;
	}

	void MoveLRCamera(float speed)
	{
		Vector3 v;
		v = view - pos;

		v = v*Up;

		v.y = 0;
		v.unitize();

		pos += v*speed;
		view += v*speed;
	}
// 
// 	Vector3 GetAngle()
// 	{
// 		return angle;
// 	}
// 
// 	void SetAngle(Vector3 angle)
// 	{
// 		this->angle = angle;
// 	}
// 
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
	Vector3 view;
	Vector3 angle;
	Vector3 Up;
	//Quaternion q;
};