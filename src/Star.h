//#include "Math/Quaternion.h"
#include "Math/Vector3.h"

class Star
{
public:
	Star();
	Star(Vector3);
	virtual ~Star();
	void Init();

	void Draw();
	//Quaternion	q;
	Vector3 R;
};