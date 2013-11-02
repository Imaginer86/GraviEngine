#pragma once
#include "Vector3D.h"
class Camera{
public:
	Camera():pos(0,0,0), angle(0,0,0)
	{}
	virtual  ~Camera() {};
//private:
	Vector3D pos;
	Vector3D angle;
};