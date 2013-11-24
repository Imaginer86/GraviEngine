#pragma once
#include "Entity.h"
#include "Vector3.h"
#include "Color.h"

class Line: public Entity
{
public:
	Line():Entity(), pos2(1, 1, 1), r(1)
	{
		this->color.r = 1.0f;
		this->color.g = 1.0f;
		this->color.b = 1.0f;
		this->color.a = 1.0f;
	}
	virtual ~Line(void){};

	float GetR()
	{
		return r;
	}

	void SetR(float r)
	{
		this->r = r;
	}

	Vector3 GetPos2()
	{
		return pos2;
	}

	void SetPos2(Vector3 pos2)
	{
		this->pos2 = pos2;
	}

	Color4f GetColor()
	{
		return color;
	}

	void SetColor(Color4f color)
	{
		this->color = color;
	}

private:
	//float m;
	//Vector3 pos1;
	Vector3 pos2;
	float r;
	Color4f color;
};

