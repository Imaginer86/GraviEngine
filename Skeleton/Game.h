#pragma once
#include "Types.h"
#include "GameBase.h"
#include "Entity/Entity.h"
#include "Entity/Sky.h"
#include "Math/Math.h"
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

	virtual void Init();								// this method will call the init() method of every Entity;

	virtual void Release();							// delete the entities created;

	virtual void Update(float32 dt);

	virtual void Draw();

	virtual bool SaveData(const std::string& fileName);

	virtual bool LoadData(const std::string& fileName);

	void AddMass(float32 m, float32 r, const Vector3f& pos, const Vector3f& vel, const Math::Color4f& color);

	void AddBox(float32 m, const Vector3f& size, const Vector3f& pos, const Vector3f& vel, const Quaternion& q, const Quaternion& qVel, const Math::Color4f& color);

	void AddSmoker(const Vector3f& pos, const Vector3f& rand, const Vector3f& vel0, const Vector3f& vel, const Math::Color4f& color, unsigned numParticles, bool createCollision);

	Vector3f GraviForce(int a, int b);

	void SimVel(float32 dt);
	void Solve(float32 dt);							// no implementation because no forces are wanted in this basic container;
 	void Simulate(float32 dt);					// Iterate the masses by the change in time;
	void AddGraviAcc(float32 dt);
	void AddWindAcc(float32 dt);
	void Collision(float32 dt);

	bool InterPlanePoint(Vector3f pr, Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3);

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

	void SetBGraviMasses(bool bGraviMasses_)
	{
		bGraviMasses = bGraviMasses_;
	}

	bool GetBGraviMasses()
	{
		return bGraviMasses;
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

	void SetGraviAcc(const Vector3f& graviAcc_)
	{
		graviAcc = graviAcc_;
	}

	void SetNumMasses(unsigned numMasses_)
	{
		numMasses = numMasses_;
	}

	unsigned GetNumMasses()
	{
		return numMasses;
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

	Vector3f GetGraviAcc()
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

	unsigned numMasses;
	unsigned numBoxes;
	unsigned numSmokers;
	unsigned numModels;

	bool bGraviMasses;
	bool bGraviAcc;
	bool bWindAcc;
	bool bCollisions;

	unsigned numEntitys;
	Entity** Entities;

	Vector3f graviAcc;

	Sky* mSky;
};

inline Game::Game()
: numEntitys(0)
, bGraviMasses(false)
, bGraviAcc(false)
, bWindAcc(false)
, bCollisions(false)
, graviAcc(0, 0, 0)
{
}

inline Game::~Game()
{
}
