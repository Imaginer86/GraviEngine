#pragma once
#include "Entity.h"

class Ship: public Entity
{
public:
	Ship() {}
	virtual ~Ship() {}

	virtual void draw() {}
};
