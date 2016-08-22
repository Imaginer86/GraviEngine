#pragma once
#include "../Math/Quaternion.h"
#include "../Math/Vector3f.h"
#include "../Math//Color.h"
//#include <vector>

//#include "Star.h"

namespace Physics
{

	class Sky
	{
	public:
		Sky();
		virtual ~Sky();	
	
		virtual void Init(unsigned numStars);
		virtual void Release();	
		virtual void Draw();

		void Randomize();

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
		float RMax;
		float RMin;
		Math::Vector3f *Pos;
		float *r;
		Math::Color4f *color;
	};

}