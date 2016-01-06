#pragma once
#include "../Constans.h"

class Random
{
public:
	static Random& Instance()
	{
		static Random SingleRender;
		return SingleRender;
	}

	Random() {}
	virtual ~Random() {}


	float randf();
	float64 randf64();
	void randomize();
};