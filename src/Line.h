#pragma once
#include "Vector3D.h"
#include "Color.h"

class Line
{
public:
	Line():m(1.0f), pos1(0, 0, 0), pos2(1, 1, 1), r(1)
	{
		this->color.r = 1.0f;
		this->color.g = 1.0f;
		this->color.b = 1.0f;
		this->color.a = 1.0f;
	}
	virtual ~Line(void){};

//private:
	float m;
	Vector3D pos1;
	Vector3D pos2;
	float r;
	Color4f color;
};

