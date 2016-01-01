#pragma once
#include <vector>
#include "Entities\Entity.h"
#include "Math\Quaternion.h"


class Game
{
public:

	Game();

	virtual ~Game(void);

	static Game& Instance()
	{
		static Game SingleGame;
		return SingleGame;
	}

	void Release();							// delete the entities created;

    void AddMass(float m, float r, const Vector3& pos, const Vector3& vel, const Color4f& color);

	void AddBox(float m, const Vector3& size, const Vector3& pos, const Vector3& vel, const Quaternion& q, const Quaternion& qVel, const Color4f& color);

	void AddSmoker(const Vector3& pos, const Vector3& rand, const Vector3& vel0, const Vector3& vel, const Color4f& color, unsigned long numParticles);

//	void SetLine(float m, float r, float h, Vector3 pos, Quaternion q, Color4f color);

	void Update(float dt);

	void Draw();
	
	Vector3 GraviForce(int a, int b);

	void Init();								// this method will call the init() method of every mass;
 	void Solve();							// no implementation because no forces are wanted in this basic container;
 	void Simulate(float dt);					// Iterate the masses by the change in time;
	void AddGraviAcc(float dt);
	void AddWindAcc(float dt);
	void Collision(float dt);

	bool InterPlanePoint(Vector3 pr, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3);

	void SetNumEntities(unsigned entities)
	{
		numEntitys = entities;
	}

	int GetNumEntities()
	{
		return numEntitys;
	}

	void SetNumStars(unsigned long numStars, bool randomize = true);

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
