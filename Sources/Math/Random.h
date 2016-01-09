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

	void randomize();

	float32 randf();
	float32 randfd();

	float32 randf(float32 a, float32 b);
};