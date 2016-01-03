#pragma once
#include "../Math/Vector3.h"
#include "../Math/Color.h"

class WaveOut
{
public:
	WaveOut()
	{}
	virtual ~WaveOut(){}

	void Set(const Vector3& pos_, unsigned numR_, unsigned numRo_, float w_, float width_, float height_, const Color4f& _color)
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
	Vector3 pos, posW;
	unsigned numR, numRo;
	float w;
	float width, height;
	Color4f color;
};