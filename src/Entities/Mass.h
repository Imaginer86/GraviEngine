#pragma once
#include "Entity.h"

class Mass: public Entity
{
public:	
	Mass();

	Mass(float m_, float r_, Vector3 pos_, Vector3 vel_);								// Constructor	

	virtual ~Mass(){};	

	void Set(float m_, float r_, Vector3 pos_, Vector3 v_, Color4f color_);

	virtual float GetR()
	{
		return r;
	}

	virtual void Draw();

private:
	float r;
};
