#pragma once
#include "Entity.h"

class Mass: public Entity
{
public:	
	Mass();

	Mass(float64 m_, float64 r_, Vector3d pos_, Vector3d vel_);								// Constructor	

	virtual ~Mass(){};	

	void Set(float64 m_, float64 r_, Vector3d pos_, Vector3d v_, Color4f color_);

	virtual float64 GetR()
	{
		return r;
	}

	virtual void Draw();

private:
	float64 r;
};
