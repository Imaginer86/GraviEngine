#pragma once
#include "../Math/Vector3d.h"
#include "../Math/Color.h"

class WaveOut
{
public:
	WaveOut()
	{}
	virtual ~WaveOut(){}

	void Set(const Vector3d& pos_, unsigned numR_, unsigned numRo_, float64 w_, float64 width_, float64 height_, const Color4f& _color)
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
	Vector3d pos, posW;
	unsigned numR, numRo;
	float64 w;
	float64 width, height;
	Color4f color;
};