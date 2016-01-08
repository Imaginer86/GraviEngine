#pragma once
#include <vector>
#include "../Sources/GameBase.h"
#include "../Sources/Entities/Entity.h"
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

	virtual bool LoadData(unsigned fileNum);

	virtual void Release();							// delete the entities created;

	virtual void Init();								// this method will call the init() method of every mass;

	virtual void Update(float64 dt);

	virtual void Draw();

	void SetNumStars(unsigned long numStars, bool randomize = true);

    void AddMass(float64 m, float64 r, const Vector3& pos, const Vector3& vel, const Color4f& color);

	void AddBox(float64 m, const Vector3& size, const Vector3& pos, const Vector3& vel, const Quaternion& q, const Quaternion& qVel, const Color4f& color);

	void AddSmoker(const Vector3& pos, const Vector3& rand, const Vector3& vel0, const Vector3& vel, const Color4f& color, unsigned long numParticles);

	Vector3 GraviForce(int a, int b);

	void Solve();							// no implementation because no forces are wanted in this basic container;
 	void Simulate(float64 dt);					// Iterate the masses by the change in time;
	void AddGraviAcc(float64 dt);
	void AddWindAcc(float64 dt);
	void Collision(float64 dt);

	bool InterPlanePoint(Vector3 pr, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3);

	void SetNumEntities(unsigned entities)
	{
		numEntitys = entities;
	}

	int GetNumEntities()
	{
		return numEntitys;
	}

	void SetBGraviMasses(bool bGraviMasses_)
	{
		bGraviMasses = bGraviMasses_;
	}

	void SetBGraviAcc(bool bGraviAcc_)
	{
		bGraviAcc = bGraviAcc_;
	}

	void SetBWindAcc(bool bWindAcc_)
	{
		bWindAcc = bWindAcc_;
	}

	void SetBCollisions(bool bCollisions_)
	{
		bCollisions = bCollisions_;
	}

	void SetGraviAcc(Vector3 graviAcc_)
	{
		this->graviAcc = graviAcc_;
	}

private:	
	//vector<Vector3> globalForces;
	unsigned numEntitys;
	std::vector<Entity*> Entities;
	//list<Entity> Entities;
	bool bGraviMasses;
	bool bGraviAcc;
	bool bWindAcc;
	bool bCollisions;
	Vector3 graviAcc;
};
