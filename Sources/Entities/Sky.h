#pragma once
#include "../Math/Quaternion.h"
#include "../Math/Vector3.h"
#include "../Math//Color.h"
//#include <vector>

//#include "Star.h"

class Sky
{
public:
	Sky();
	virtual ~Sky();	
	
	void Init(unsigned long numStars);
	void Randomize();
	void Draw();

	void SetNumStars(unsigned long numStars_)
	{
		numStars = numStars_;
	}

	unsigned long GetNumStars()
	{
		return numStars;
	}

//private:
	//std::vector <Star> Stars;
	//Star *Stars;

private:
	unsigned long numStars;
	//Quaternion *q;
	Vector3 *R;
	float64 *r;
	Color4f *color;
};