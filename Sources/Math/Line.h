#pragma once
#include "Vector3f.h"

struct Line
{
	Vector3f p;
	Vector3f k;	

	Line()
	{

	}

	Line(Vector3f pa, Vector3f pb)
	{
		p = pb;
		k = pb - pa;
	}

	void FromAxic(const Vector3f& p_, const Vector3f& k_)
	{
		p = p_;
		k = k_;
	}
};