#pragma once
#include "Entity.h"

class Mass: public Entity
{
public:	

	Mass();
	Mass(float32 m_, float32 r_, Vector3f pos_, Vector3f vel_, Math::Color4f color_);								// Constructor	

	virtual ~Mass(){};	

	void Set(float32 m_, float32 r_, Vector3f pos_, Vector3f v_, Math::Color4f color_);

	virtual float32 GetR()
	{
		return r;
	}

	virtual void Draw();

private:
	float32 r;
};

inline Mass::Mass()
: Entity()
, r(1.0f)
{

}


inline Mass::Mass(float32 m_, float32 r_, Vector3f pos_, Vector3f vel_, Math::Color4f color_)
: Entity(m_, pos_, vel_, color_)
, r(r_)
{
}
