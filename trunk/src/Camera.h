#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"
class Camera{
public:
	Camera():pos(0,0,0), angle(0,0,0)
	{}
	virtual  ~Camera() {};
//private:
	Vector3 pos;
	Vector3 angle;
};