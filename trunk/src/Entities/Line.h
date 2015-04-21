#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Color.h"

class Line: public Entity
{
public:

	Line()
	: Entity()
	, r(1.0f)
	, h(1.0f)
	, q(0.0f, 0.0f, 0.0f, 0.0f)
	{
		this->color.r = 1.0f;
		this->color.g = 1.0f;
		this->color.b = 1.0f;
		this->color.a = 1.0f;
	}

	virtual ~Line(){};

	virtual void function()
	{
	}

	void SetR(float r)
	{
		this->r = r;
	}

	virtual float GetR()
	{
		return r;
	}

	void SetH(float h)
	{
		this->h = h;
	}

	virtual float GetH()
	{
		return h;
	}

// 	Vector3 GetPos2()
// 	{
// 		return pos2;
// 	}
// 
// 	void SetPos2(Vector3 pos2)
// 	{
// 		this->pos2 = pos2;
// 	}

	void SetQuaternion(Quaternion q)
	{
		this->q = q;
	}

	Quaternion GetQuaternion()
	{
		return q;
	}

	Color4f GetColor()
	{
		return color;
	}

	void SetColor(Color4f color)
	{
		this->color = color;
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

	virtual void Draw();

	virtual void Collision(Entity& Entity)
	{
	}

	virtual bool IsColisions(Entity& Entity)
	{
		return false;
	}

	virtual float ProcessColisions(Entity& entity)
	{
		return 0.f;
	}

private:
	//Vector3 pos2;
	float h;
	float r;
	Quaternion q;
};

