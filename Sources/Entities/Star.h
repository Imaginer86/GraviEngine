#pragma once
#include "../Math/Quaternion.h"
#include "../Math/Vector3d.h"

class Star
{
public:
	Star();
	Star(Vector3d, Quaternion);
	virtual ~Star();
	void Init();

	void Draw();
	Quaternion	q;
	Vector3d R;
};