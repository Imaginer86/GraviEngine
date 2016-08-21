#pragma once
#include "GameBase.h"
#include "Physics/Entity.h"
#include "Physics/Sky.h"
#include "Math/Math.h"
#include "Math/Vector2f.h"
#include "Math/Vector3f.h"
#include "Math/Quaternion.h"


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

	bool initialize();

	virtual void Init();								// this method will call the init() method of every Entity;

	virtual void Release();							// delete the entities created;

	virtual void Update(float dt);

	virtual void Draw();

	virtual bool SaveData(const std::string& fileName);

	virtual bool LoadData(const std::string& fileName);

	void AddSphere(float m, float r, const Math::Vector3f& pos, const Math::Vector3f& vel, const Math::Color4f& color);
	void AddPlane(float m, const Math::Vector2f& size, const Math::Vector3f& pos, const Math::Vector3f& vel, const Math::Quaternion& q, const Math::Quaternion& qVel, const Math::Color4f& color);
	void AddBox(float m, const Math::Vector3f& size, const Math::Vector3f& pos, const Math::Vector3f& vel, const Math::Quaternion& q, const Math::Quaternion& qVel, const Math::Color4f& color);
	void AddWave(float m, unsigned sizeN, unsigned sizeM, float size, const Math::Vector3f& pos, const Math::Vector3f& vel, const Math::Quaternion& q, const Math::Quaternion& qVel, const Math::Color4f& color);
	void AddSmoker(const Math::Vector3f& pos, const Math::Vector3f& rand, const Math::Vector3f& vel0, const Math::Vector3f& vel, const Math::Color4f& color, unsigned numParticles, bool createCollision);
	bool AddModel(const std::string& fileName, const float m, const Math::Vector3f& pos, const Math::Vector3f& vel, const Math::Color4f& color);
	bool AddVideo(const std::string& fileName, const float m, const Math::Vector2f& size, const Math::Vector3f& pos, const Math::Vector3f& vel, const Math::Quaternion& q, const Math::Quaternion& qVel, const Math::Color4f& color);

	Math::Vector3f GraviForce(int a, int b);

	void SimVel(float dt);
	void Solve(float dt);							// no implementation because no forces are wanted in this basic container;
 	void Simulate(float dt);					// Iterate the masses by the change in time;
	void AddGraviAcc(float dt);
	void AddWindAcc(float dt);
	void Collision(float dt);

	bool InterPlanePoint(Math::Vector3f pr, Math::Vector3f p0, Math::Vector3f p1, Math::Vector3f p2, Math::Vector3f p3);

	void SetNumStars(unsigned numStars, bool randomize = true);

	unsigned GetNumStars()
	{
		return mSky->GetNumStars();
	}

	void SetNumEntities(unsigned numEntities_);

	int GetNumEntities()
	{
		return numEntitys;
	}

	void SetBGraviSpherees(bool bGraviSpherees_)
	{
		bGraviSpherees = bGraviSpherees_;
	}

	bool GetBGraviSpherees()
	{
		return bGraviSpherees;
	}

	void SetBGraviAcc(bool bGraviAcc_)
	{
		bGraviAcc = bGraviAcc_;
	}

	bool GetBGraviAcc()
	{
		return bGraviAcc;
	}

	void SetBWindAcc(bool bWindAcc_)
	{
		bWindAcc = bWindAcc_;
	}

	bool GetBWindAcc()
	{
		return bWindAcc;
	}

	void SetBCollisions(bool bCollisions_)
	{
		bCollisions = bCollisions_;
	}

	bool GetBCollisions()
	{
		return bCollisions;
	}

	void SetNumSpherees(unsigned numSpherees_)
	{
		numSpherees = numSpherees_;
	}

	unsigned GetNumSpherees()
	{
		return numSpherees;
	}

	void SetNumBoxes(unsigned numBoxes_)
	{
		numBoxes= numBoxes_;
	}

	unsigned GetNumBoxes()
	{
		return numBoxes;
	}

	void SetNumSmokers(unsigned numSmokers_)
	{
		numSmokers = numSmokers_;
	}

	unsigned GetNumSmokers()
	{
		return numSmokers;
	}

	void SetNumModels(unsigned numModels_)
	{
		numModels = numModels_;
	}

	void SetGraviAcc(const Math::Vector3f& graviAcc_)
	{
		graviAcc = graviAcc_;
	}

	Math::Vector3f GetGraviAcc()
	{
		return graviAcc;
	}

	virtual void SetSceneName(const std::string& sceneName_)
	{
		gSceneName = sceneName_;
	}

	virtual std::string GetSceneName()
	{
		return gSceneName;
	}

private:
	std::string  gSceneName;

	unsigned countAddEntities;

	unsigned numSpherees;
	unsigned numBoxes;
	unsigned numSmokers;
	unsigned numModels;

	bool bGraviSpherees;
	bool bGraviAcc;
	bool bWindAcc;
	bool bCollisions;

	unsigned numEntitys;
	Physics::Entity** Entities;

	Math::Vector3f graviAcc;

	Physics::Sky* mSky;
};

inline Game::Game()
: countAddEntities(0)
, numEntitys(0)
, bGraviSpherees(false)
, bGraviAcc(false)
, bWindAcc(false)
, bCollisions(false)
, graviAcc(0, 0, 0)
{
}

inline Game::~Game()
{
}
