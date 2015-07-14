#pragma once
#include "Vector3.h"

struct Line
{
	Vector3 p;
	Vector3 k;	

	Line(Vector3 pa, Vector3 pb)
	{
		p = pb;
		l = pb - pa;
	}
}