#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

class Camera
{
public:

	Vector3 pos;
	Quaternion Q;

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

	Vector3 GetView();

	void Init()
	{
		pos = Vector3(10.0f, 10.0f, 0.0f);
		Q = Quaternion(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void Interpolate(Quaternion& q_)
	{
		Q *= q_;
	}

	void SetPos(Vector3& pos_)
	{
		pos = pos_;
	}

	Vector3& GetPos()
	{
		return pos;
	}

	Quaternion GetQuaternion()
	{
		return Q;
	}

	void SetQuaternion(Quaternion& q_)
	{
		Q = q_;
	}

	
};