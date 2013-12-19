#pragma once
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"
class Camera{
public:
	Camera():pos(0,0,0), angle(0,0,0)
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

	Vector3 GetPos2()
	{
		return pos2;
	}

	void SetPos2(Vector3 pos2)
	{
		this->pos2 = pos2;
	}

	void AddPosX(float x)
	{
		this->pos.x += x;
	}

	void AddPosY(float y)
	{
		this->pos.y += y;
	}

	void AddPosZ(float z)
	{
		this->pos.z += z;
	}

	Vector3 GetAngle()
	{
		return angle;
	}

	void SetAngle(Vector3 angle)
	{
		this->angle = angle;
	}

	void AddAngleX(float x)
	{
		this->angle.x += x;
	}

	void AddAngleY(float y)
	{
		this->angle.y += y;
	}

	void AddAngleZ(float z)
	{
		this->angle.z += z;
	}
private:
	Vector3 pos;
	Vector3 pos2;
	Vector3 angle;
};