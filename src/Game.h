#pragma once
#include <vector>
#include "Entities\Entity.h"
#include "Math\Quaternion.h"

class Game
{
public:

	Game();

	virtual ~Game(void);

	void Release();							// delete the entities created;

	void SetNumEntities(int entities)
	{
		numEntitys = entities;
	}

	int GetNumEntities()
	{
		return numEntitys;
	}

    void SetMass(float m, float r,  Vector3 pos, Vector3 vel, Color4f color);

	void SetBox(float m, Vector3 size, Vector3 pos, Vector3 vel, Quaternion q, Quaternion qVel, Color4f color);

//	void SetLine(float m, float r, float h, Vector3 pos, Quaternion q, Color4f color);

	void Game::SetGraviAcc(Vector3 graviAcc_)
	{
		this->graviAcc = graviAcc_;
	}

	void Update(float dt);

	void Draw();
	
	Vector3 GraviForce(int a, int b);

	void Init();								// this method will call the init() method of every mass;
 	void Solve();							// no implementation because no forces are wanted in this basic container;
 	void Simulate(float dt);					// Iterate the masses by the change in time;
	void AddGraviAcc(float dt);

	void Collision(float dt);

private:
	//vector<Vector3> globalForces;
	int numEntitys;
	std::vector<Entity*> Entities;
	//list<Entity> Entities;
	Vector3 graviAcc;
};
