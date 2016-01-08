﻿#pragma once
#include "../Sources/GameBase.h"
#include "../Sources/Entities/Entity.h"
#include "../Sources/Entities/Sky.h"
#include "../Sources/Math/Math.h"
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

	virtual bool SaveData();

	virtual bool LoadData(unsigned fileNum);

	virtual void Release();							// delete the entities created;

	virtual void Init();								// this method will call the init() method of every mass;

	virtual void Update(float64 dt);

	virtual void Draw();

	void AddMass(float64 m, float64 r, const Vector3& pos, const Vector3& vel, const Color4f& color);

	void AddBox(float64 m, const Vector3& size, const Vector3& pos, const Vector3& vel, const Quaternion& q, const Quaternion& qVel, const Color4f& color);

	void AddSmoker(const Vector3& pos, const Vector3& rand, const Vector3& vel0, const Vector3& vel, const Color4f& color, unsigned long numParticles, bool createCollision);

	Vector3 GraviForce(int a, int b);

	void Solve();							// no implementation because no forces are wanted in this basic container;
 	void Simulate(float64 dt);					// Iterate the masses by the change in time;
	void AddGraviAcc(float64 dt);
	void AddWindAcc(float64 dt);
	void Collision(float64 dt);

	bool InterPlanePoint(Vector3 pr, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3);

	void SetNumStars(unsigned long numStars, bool randomize = true);

	unsigned long GetNumStars()
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

	void SetGraviAcc(Vector3 graviAcc_)
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

	Vector3 GetGraviAcc()
	{
		return graviAcc;
	}

private:
	unsigned numMasses;
	unsigned numBoxes;
	unsigned numSmokers;

	bool bGraviMasses;
	bool bGraviAcc;
	bool bWindAcc;
	bool bCollisions;

	unsigned numEntitys;
	Entity** Entities;

	Vector3 graviAcc;

	Sky* mSky;
};
