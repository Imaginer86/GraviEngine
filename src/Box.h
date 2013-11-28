#pragma once
#include "Entity.h"
#include "Vector3.h"
#include "Color.h"

class Box: public Entity
{
public:
	Box()
	: Entity()
	, size(1.0, 1.0, 1.0)
	, angle(0.0, 0.0, 0.0)
	{
		this->color.r = 1.0f;
		this->color.g = 1.0f;
		this->color.b = 1.0f;
		this->color.a = 1.0f;
	}
	virtual ~Box(){};

	Vector3 GetSize()
	{
		return size;
	}

	void SetSize(Vector3 size)
	{
		this->size = size;
	}

	Vector3 GetAngle()
	{
		return angle;
	}

	void SetAngle(Vector3 angle)
	{
		this->angle = angle;
	}

	Color4f GetColor()
	{
		return color;
	}

	void SetColor(Color4f color)
	{
		this->color = color;
	}

	virtual float GetR()
	{
		return 0.0f;
	}

	virtual void applyForce(Vector3 force)
	{
		return;
	}

	virtual void simulateForce(float dt)
	{
		return;
	}

	virtual void init()
	{
		return;
	}


private:	
	Vector3 size;
	Vector3 angle;
};
