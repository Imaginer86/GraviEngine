#include "Camera.h"
#include "Math/Matrix3.h"
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

Vector3 Camera::GetView()
{
	Vector3 view(0,0,1);	
	Matrix3 RotateM;
	Vector3 a;
	float angle;
	q.toAxisAngle(a, angle);
	RotateM[0][0] = cosf(angle) + (1 - cosf(angle))*a.x*a.x;
	RotateM[0][1] = (1 - cosf(angle))*a.x*a.y - sinf(angle)*a.z;
	RotateM[0][2] = (1 - cosf(angle))*a.x*a.z + sinf(angle)*a.y;
	RotateM[1][0] = (1 - cosf(angle))*a.y*a.x + sinf(angle)*a.z;
	RotateM[1][1] = cosf(angle) + (1 - cosf(angle))*a.y*a.y;
	RotateM[1][2] = (1 - cosf(angle))*a.y*a.z - sinf(angle)*a.x;
	RotateM[2][0] = (1 - cosf(angle))*a.z*a.x - sinf(angle)*a.y;
	RotateM[2][1] = (1 - cosf(angle))*a.z*a.y - sinf(angle)*a.x;
	RotateM[2][2] = cosf(angle) + (1 - cosf(angle))*a.z*a.z;
	view = RotateM * view;

	//view.unitize();

	return view;
}


void Camera::MoveCamera(float speed)
{
	Vector3 v = GetView();
	pos += v*speed;
}

void Camera::MoveLRCamera(float speed)
{
	Vector3 b(0,-1,0);
	Vector3 v = GetView();
	b = b*v;
	pos += b*speed;
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
