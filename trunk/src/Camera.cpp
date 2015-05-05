#include "Camera.h"
//#include "Math/Matrix3.h"

//void Camera::SetQuaternion(Quaternion q)
//{
//	this->q = q;
//}

//void Camera::SetQuaternion(Vector3 pos, Vector3 view, Vector3 Up)
//{
//	this->pos = pos;
//	this->view = view;
//	this->Up = Up;

//	this->q.fromAxisAngle(view-pos, (view-pos).dotProduct(Up));
//}

void Camera::RotateUpDown(float anglef)
{
	Vector3 axic(1, 0, 0);
	Quaternion qn;
	qn.fromAxisAngle(axic, anglef);
	q *= qn;
	q.normalize();
}


void Camera::RotateLR(float anglef)
{

	Vector3 axic(0, 1, 0);
	Quaternion qn;
	qn.fromAxisAngle(axic, anglef);
	q *= qn;
	q.normalize();

}

void Camera::MoveCamera(float speed)
{
	Vector3 b(0,0,1);

	//Quaternion qn(Vector3(1, 0, 0), 0);
	//qn.normalize();
	
	//q *= qn;
	//b = 
	
	Vector3 a;
	float angle;
	q.toAxisAngle(a, angle);

	Vector3 c = a*b;
	b = c*a;

	//v = v*Vector3(0, 1, 0);

	if (angle <= 0.0f)
	{
//		pos -= v*speed;
	}
	else
	{
//		pos -= v*speed;
	}

	auto t = GetView();




//	v = view - pos;

	//v.y = 0;
	//v.unitize();

	//pos += v*speed;
//	view += v*speed;
}

void Camera::MoveLRCamera(float speed)
{
	Vector3 v;
	float angle;
	q.toAxisAngle(v, angle);
	v.unitize();
	pos += v*speed;
}



//void Camera::SetQuaternion(Vector3& cameraPos, Vector3& cameraView, Vector3& cameraUp)
//{
//	Vector3 a = this->Up;
//	Vector3 b = cameraView - cameraView;
//	float angle = acosf(a.dotProduct(b)/(a.length()*b.length()));	
//}

//void Camera::SetQuaternionFromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees)
//{
//	Vector3 lQ;
//	//lQ.x = 
//}
