#pragma once
#include "Entity.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Color.h"

class Box: public Entity
{
public:

	Box()
	: Entity()
	, size(1.0, 1.0, 1.0)
	, angle(0.0, 0.0, 0.0)
	, force(0.0f, 0.0f, 0.0f)
	, q(0.0f,0.0f,0.0f,0.0f)
	, qVel(0.0f, 0.0f, 0.0f, 0.0f)
	{
		this->color.r = 1.0f;
		this->color.g = 1.0f;
		this->color.b = 1.0f;
		this->color.a = 1.0f;
	}

	virtual ~Box(){};

	virtual void function()
	{
	}

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
		this->q.fromAngleXYZ(angle);
	}

	Color4f GetColor()
	{
		return color;
	}

	void SetColor(Color4f color)
	{
		this->color = color;
	}

	Vector3 GetAngleVel()
	{
		return angleVel;
	}

	void SetAngleVel(Vector3 angleVel)
	{
		this->angleVel = angleVel;
		this->qVel.fromAngleXYZ(angleVel);
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
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
		// The change is proportinal with the acceleration (force / m) and change in time

		pos += vel * dt;						// Change in position is added to the position.
		// Change in position is velocity times the change in time

		angle += angleVel*dt;

		Quaternion temp = qVel;
		Vector3 temp2(temp.x, temp.y, temp.z);
		temp2.unitize();
		float angle = acosf(temp.w);
		angle *= dt;
		Quaternion temp3(cosf(angle), temp2.x*sinf(angle), temp2.y*sinf(angle), temp2.z*sinf(angle));
		//temp.normalize();
		//temp.w *= dt;
		//temp.normalize();
		//if (dt==0.0f)
			//temp = Quaternion(1,0,0,0);
		q *= temp3;

		return;
	}

	virtual void init()
	{
		force.x = 0;
		force.y = 0;
		force.z = 0;
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
	Vector3 size;
	Vector3 angle;
	Vector3 angleVel;
	Vector3 force;
	Quaternion q;
	Quaternion qVel;
};
