#pragma once
#include "../Math/Quaternion.h"
#include "../Math/Vector3.h"
//#include <vector>

//#include "Star.h"

class Sky
{
public:
	unsigned long numStars;

	Sky();
	Sky(long numStars);
	virtual ~Sky();	
	
	void Init(unsigned long numStars);
	void Randomize();
	void Draw();

//private:
	//std::vector <Star> Stars;
	//Star *Stars;

protected:
	//Quaternion *q;
	Vector3 *R;
	float *r;
};