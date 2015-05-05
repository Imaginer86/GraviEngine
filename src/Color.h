#pragma once
struct Color4f{
	float r;
	float g;
	float b;
	float a;

	Color4f()
	:r(0.0f)
	,g(0.0f)
	,b(0.0f)
	,a(0.0f)
	{}

	Color4f(float r, float g, float b, float a)
	:r(r)
	,g(g)
	,b(b)
	,a(a)
	{}

	~Color4f()
	{}
};