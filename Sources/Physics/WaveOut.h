#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

class WaveOut
{
public:
	WaveOut()
	{}
	virtual ~WaveOut(){}

	void Set(const Vector3f& pos_, unsigned numR_, unsigned numRo_, float32 w_, float32 width_, float32 height_, const Math::Color4f& _color)
	{
		pos = pos_;
		numR = numR_;
		numRo = numRo_;
		w = w_;
		width = width_;
		height = height_;
		color = _color;
	}
	virtual void Draw();
private:
	Vector3f pos, posW;
	unsigned numR, numRo;
	float32 w;
	float32 width, height;
	Math::Color4f color;
};