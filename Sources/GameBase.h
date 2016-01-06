#pragma once
#include <vector>
#include "../Sources/Math/Quaternion.h"

class GameBase
{
public:

	GameBase();

	virtual ~GameBase(void);

	static GameBase& Instance()
	{
		static GameBase SingleGameBase;
		return SingleGameBase;
	}

	virtual bool LoadData(unsigned fileNum);

	virtual void Init();								// this method will call the init() method of every mass;

	virtual void Release();							// delete the entities created;

	virtual void Update(float64 dt);

	virtual void Draw();

	void SetSceneNum(unsigned sceneNum)
	{
		gSceneNum = sceneNum;
	}

	unsigned GetSceneNum()
	{
		return gSceneNum;
	}

private:
	unsigned gSceneNum;
};
