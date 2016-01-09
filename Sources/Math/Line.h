#pragma once
#include "Vector3d.h"

struct Line
{
	Vector3d p;
	Vector3d k;	

	Line()
	{

	}

	Line(Vector3d pa, Vector3d pb)
	{
		p = pb;
		k = pb - pa;
	}

	void FromAxic(const Vector3d& p_, const Vector3d& k_)
	{
		p = p_;
		k = k_;
	}
};