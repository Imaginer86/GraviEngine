#pragma once
#include "Vector3f.h"
#include "Matrix3.h"
#include "Line.h"
#include "Math.h"

namespace Math
{

struct Plane
{
	float a, b, c, d;
	Plane()
	: a(0.0f)
	, b(0.0f)
	, c(0.0f)
	, d(0.0f)
	{}
	
	Plane(float a_, float b_, float c_, float d_)
	: a(a_)
	, b(b_)
	, c(c_)
	, d(d_)
	{}

	Plane(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3);

	Vector3f proj(Vector3f p);
	float distance(Vector3f p);
};

inline Plane::Plane(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3)
{
	Matrix3 A(	1.0f, p1.y, p1.z,
				1.0f, p2.y, p2.z,
				1.0f, p3.y, p3.z	);
	Matrix3 B(	p1.x, 1.0f, p1.z,
				p2.x, 1.0f, p2.z,
				p3.x, 1.0f, p3.z	);
	Matrix3 C(	p1.x, p1.y, 1.0f,
				p2.x, p2.y, 1.0f,
				p3.x, p3.y, 1.0f	);
	Matrix3 D(	p1.x, p1.y, p1.z,
				p2.x, p2.y, p2.z,
				p3.x, p3.y, p3.z	);

	this->a = A.det();
	this->b = B.det();
	this->c = C.det();
	this->d = -D.det();
}

inline Vector3f Plane::proj(Vector3f p)
{
	float nn = a*a + b*b + c*c;
	Vector3f pr;
	pr.x = (b*b*p.x + c*c*p.x - a*b*p.y - a*c*p.z - a*d) / nn;
	pr.y = (a*a*p.y + c*c*p.y - a*b*p.x - b*c*p.z - b*d) / nn;
	pr.z = (a*a*p.z + b*b*p.z - a*c*p.x - b*c*p.y - c*d) / nn;
	return pr;
}

inline float Plane::distance(Vector3f p)
{
	return abs((a*p.x + b*p.y + c*p.z - d) / sqrt(a*a + b*b + c*c));
}

}