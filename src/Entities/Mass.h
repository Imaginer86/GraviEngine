#pragma once
#include "Entity.h"

class Mass: public Entity
{
public:	
	Mass();

	Mass(float m_, float r_, Vector3 pos_, Vector3 vel_);								// Constructor	

	virtual ~Mass(){};	

	void Set(float m, float r, Vector3 p, Vector3 v, Color4f color);

	virtual float GetR()
	{
		return r;
	}

	virtual void Draw();

private:
	float r;
};
