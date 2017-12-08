#pragma once
#include "Vector3f.h"
#include "Quaternion.h"
class Camera
{
public:
	Vector3f	pos;
	Quaternion	q;

	Camera()
	{
	}

	Camera(const Vector3f& _pos, const Quaternion& _q):pos(_pos), q(_q)
	{

	}

	~Camera()
	{
	}
};

