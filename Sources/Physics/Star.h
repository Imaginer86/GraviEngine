#pragma once
#include "../Math/Quaternion.h"
#include "../Math/Vector3f.h"

namespace Physics
{

class Star
{
public:
	Star();
	Star(Vector3f, Quaternion);
	virtual ~Star();
	void Init();

	void Draw();
	Quaternion	q;
	Vector3f R;
};

}