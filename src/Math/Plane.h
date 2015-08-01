#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include "Line.h"

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

	Plane(Vector3 p1, Vector3 p2, Vector3 p3);

	Vector3 proj(Vector3 p);
};

inline Plane::Plane(Vector3 p1, Vector3 p2, Vector3 p3)
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
	this->d = D.det();
}

inline Vector3 Plane::proj(Vector3 p)
{
	Line L;
	L.FromAxic(p, Vector3(a, b, c));
	Vector3 pr((p.x - L.p.x) / L.k.x, (p.y - L.p.y) / L.k.y, (p.z - L.p.z) / L.k.z);
	return pr;
}