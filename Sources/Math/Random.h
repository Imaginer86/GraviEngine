#pragma once

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
	void randomize();
};