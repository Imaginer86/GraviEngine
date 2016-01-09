#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

class Wave
{
public:
	Wave()
		: tGame(0.0f)
	{}
	virtual ~Wave(){}

	void Set(const Vector3f& pos_, unsigned numR_, unsigned numRo_, float32 w_, const Math::Color4f& _color)
	{
		pos = pos_;
		numR = numR_;
		numRo = numRo_;
		w = w_;
		color = _color;
	}
	virtual void Update(float32 dt_);
	virtual void Draw();
private:
	float32 tGame;
	Vector3f pos;
	unsigned numR, numRo;
	float32 w;
	Math::Color4f color;
};