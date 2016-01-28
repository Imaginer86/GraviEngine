#pragma once
#include <string>

#include "Math/Quaternion.h"

class GameBase
{
public:

	GameBase(){};

	virtual ~GameBase(void){};

// 	static GameBase& Instance()
// 	{
// 		static GameBase SingleGameBase;
// 		return SingleGameBase;
// 	}

	virtual bool LoadData(const std::string& fileName) = 0;
	virtual bool SaveData(const std::string& fileName) = 0;

	virtual void Init() = 0;								// this method will call the init() method of every mass;

	virtual void Release() = 0;							// delete the entities created;

	virtual void Update(float dt) = 0;

	virtual void Draw() = 0;

	//virtual void SetSceneNum(unsigned sceneNum) = 0;

	//virtual unsigned GetSceneNum() = 0;

	virtual void SetSceneName(const std::string& scenName_) = 0;
	virtual std::string GetSceneName() = 0;
};
