#pragma once
#include "Vector3.h"
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
	Vector3 pos1;
	Vector3 pos2;
	float r;
	Color4f color;
};

