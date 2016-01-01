#pragma once
#include "../Math/Vector3.h"
#include "../Math/Color.h"

class Wave
{
public:
	Wave()
		: tGame(0.0f)
	{}
	virtual ~Wave(){}

	void Set(const Vector3& pos_, unsigned numR_, unsigned numRo_, float w_, const Color4f& _color)
	{
		pos = pos_;
		numR = numR_;
		numRo = numRo_;
		w = w_;
		color = _color;
	}
	virtual void Update(float dt_);
	virtual void Draw();
private:
	float tGame;
	Vector3 pos;
	unsigned numR, numRo;
	float w;
	Color4f color;
};