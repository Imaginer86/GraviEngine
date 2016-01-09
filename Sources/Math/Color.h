#pragma once

namespace Math
{
	struct Color4f{
		float32 r;
		float32 g;
		float32 b;
		float32 a;

		Color4f()
		:r(0.0f)
		,g(0.0f)
		,b(0.0f)
		,a(0.0f)
		{}

		Color4f(float32 r, float32 g, float32 b, float32 a)
		:r(r)
		,g(g)
		,b(b)
		,a(a)
		{}

		~Color4f()
		{}
	};
}