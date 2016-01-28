#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

namespace Physics
{

class Wave
{
public:
	Wave()
		: tGame(0.0f)
	{}
	virtual ~Wave(){}

	void Set(const Vector3f& pos_, unsigned numR_, unsigned numRo_, float w_, const Math::Color4f& _color)
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
	Vector3f pos;
	unsigned numR, numRo;
	float w;
	Math::Color4f color;
};

}