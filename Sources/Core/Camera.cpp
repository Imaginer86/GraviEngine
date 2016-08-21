#include "Camera.h"


using namespace Core;
using namespace Math;

Camera::Camera()
:pos(0.0, 0.0, 0.0)
,q(0.0, 0.0, 1.0, 0.0)
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
	Quaternion qn;
	qn.fromAxisAngle(Vector3f(-1, 0, 0), anglef);
	qn.normalize();
	q *= qn;
	q.normalize();
}

void Camera::RotateLR(float anglef)
{
	Vector3f axic(0, 1, 0);
	Quaternion qn;
	qn.fromAxisAngle(axic, anglef);
	qn.normalize();
	q *= qn;
	q.normalize();
}

 Vector3f Camera::GetView()
 {
 	Vector3f view(0,0,1);	
 	view = q.rotate(view);
 	view.unitize();		  
 	return view;
}

void Camera::MoveCamera(float speed)
{
	Vector3f v = GetView();
	pos += v*speed;
}

void Camera::MoveLRCamera(float speed)
{
	Vector3f b(0,-1,0);
	Vector3f v = GetView();
	b = b*v;
	pos += b*speed;
}