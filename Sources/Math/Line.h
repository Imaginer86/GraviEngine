#pragma once
#include "Vector3.h"

struct Line
{
	Vector3 p;
	Vector3 k;	

	Line()
	{

	}

	Line(Vector3 pa, Vector3 pb)
	{
		p = pb;
		k = pb - pa;
	}

	void FromAxic(const Vector3& p_, const Vector3& k_)
	{
		p = p_;
		k = k_;
	}
};