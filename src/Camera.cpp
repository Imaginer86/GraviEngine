#include "Camera.h"
#include "Math/Matrix3.h"
//#include "Math/Matrix3.h"


Camera::Camera()
: pos(0,0,0)
, q(0, 1, 1, 1)
{

}

Camera::~Camera()
{

}


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