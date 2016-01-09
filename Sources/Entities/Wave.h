#pragma once
#include "../Math/Vector3d.h"
#include "../Math/Color.h"

class Wave
{
public:
	Wave()
		: tGame(0.0f)
	{}
	virtual ~Wave(){}

	void Set(const Vector3d& pos_, unsigned numR_, unsigned numRo_, float64 w_, const Color4f& _color)
	{
		pos = pos_;
		numR = numR_;
		numRo = numRo_;
		w = w_;
		color = _color;
	}
	virtual void Update(float64 dt_);
	virtual void Draw();
private:
	float64 tGame;
	Vector3d pos;
	unsigned numR, numRo;
	float64 w;
	Color4f color;
};