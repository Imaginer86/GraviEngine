#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

namespace Physics
{

class WaveOut
{
public:
	WaveOut()
	{}
	virtual ~WaveOut(){}

	void Set(const Vector3f& pos_, unsigned numR_, unsigned numRo_, float w_, float width_, float height_, const Math::Color4f& _color)
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
	float w;
	float width, height;
	Math::Color4f color;
};

}