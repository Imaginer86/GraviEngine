#pragma once

class Wave
{
public:
	Wave(){}
	virtual ~Wave(){}

	virtual void Update(float dt_);
	virtual void Draw();
private:
	float tGame;
};