#pragma once
//#include <vector>

#include "Star.h"

class Sky
{
public:
	unsigned long numStars;

	Sky();
	Sky(long numStars);
	~Sky();	
	
	bool Init(long numStars);
	void Draw();

//private:
	//std::vector <Star> Stars;
	Star *Stars;
};