#pragma once
#include "../Math/Quaternion.h"
#include "../Math/Vector3f.h"
#include "../Math//Color.h"
//#include <vector>

//#include "Star.h"

class Sky
{
public:
	Sky();
	virtual ~Sky();	
	
	void Init(unsigned numStars);
	void Release();
	void Randomize();
	void Draw();

	void SetNumStars(unsigned numStars_)
	{
		numStars = numStars_;
	}

	unsigned GetNumStars()
	{
		return numStars;
	}

//private:
	//std::vector <Star> Stars;
	//Star *Stars;

private:
	unsigned numStars;
	//Quaternion *q;
	float32 RMax;
	float32 RMin;
	Vector3f *Pos;
	float32 *r;
	Math::Color4f *color;
};