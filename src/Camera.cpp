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
	Vector3 axic(-1, 0, 0);
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
//	Matrix3 RotateM;
//	float w = q.w;
//	float x = q.x;
//	float y = q.y;
//	float z = q.z;
//	RotateM[0][0] = 1 - 2*y*y - 2*z*z;
//	RotateM[0][1] = 2*x*y - 2*z*w;
//	RotateM[0][2] = 2*x*z + 2*y*w;
//	RotateM[1][0] = 2*x*y + 2*z*w;
//	RotateM[1][1] = 1 - 2*x*x - 2*z*z;
//	RotateM[1][2] = 2*y*z - 2*x*w;
//	RotateM[2][0] = 2*x*z - 2*y*w;
//	RotateM[2][1] = 2*y*z + 2*x*w;
//	RotateM[2][2] = 1 - 2*x*x - 2*y*y;

//	view = RotateM * view;

	view = q.rotate(view);

	view.unitize();

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
