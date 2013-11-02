#pragma once
#include "Vector3D.h"
#include "Color.h"

class Box
{
public:
	Box():m(1.0), pos(0.0, 0.0, 0.0), size(1.0, 1.0, 1.0), angle(0.0, 0.0, 0.0)
	{
		this->color.r = 1.0f;
		this->color.g = 1.0f;
		this->color.b = 1.0f;
		this->color.a = 1.0f;
	}
	virtual ~Box(void){};
//private:	
	float m;
	Vector3D pos;
	Vector3D size;
	Vector3D angle;
	Color4f color;
};
