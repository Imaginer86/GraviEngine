#include "Camera.h"


using namespace Core;

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

void Camera::RotateUpDown(float32 anglef)
{
	Quaternion qn;
	qn.fromAxisAngle(Vector3f(-1, 0, 0), anglef);
	q *= qn;
	q.normalize();
}

void Camera::RotateLR(float32 anglef)
{
	Vector3f axic(0, 1, 0);
	Quaternion qn;
	qn.fromAxisAngle(axic, anglef);
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

void Camera::MoveCamera(float32 speed)
{
	Vector3f v = GetView();
	pos += v*speed;
}

void Camera::MoveLRCamera(float32 speed)
{
	Vector3f b(0,-1,0);
	Vector3f v = GetView();
	b = b*v;
	pos += b*speed;
}