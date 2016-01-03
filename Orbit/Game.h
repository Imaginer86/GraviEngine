#pragma once
#include <vector>
#include "../Sources/GameBase.h"
#include "../Sources/Math/Quaternion.h"

class Game: public GameBase
{
public:

	Game();

	virtual ~Game(void);

	static Game& Instance()
	{
		static Game SingleGame;
		return SingleGame;
	}

	void Init();								// this method will call the init() method of every mass;

	void Release();							// delete the entities created;

	void Update(float dt);

	void Draw();

private:
};
