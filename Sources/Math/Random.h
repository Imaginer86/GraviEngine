﻿#pragma once
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

	float randf();
	float randfd();

	float randf(float a, float b);
};