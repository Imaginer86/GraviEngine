#pragma once
//#include <list>
#include <vector>
#include "Math/Math.h"

#include <fstream>

using namespace Math;

#include "Entities\Entity.h"
#include "Math\Quaternion.h"

const float G = 0.01f;

class Game
{
public:
	Game()
	: numEntitys(0)
	//, Entities(null)
	, graviAcc(0, 0, 0)
	{
		fileOut = std::ofstream("out.dat", std::ios::out);
	}

	~Game(void)
	{
		fileOut.close();
	}	

	void Game::SetNumMasses( int num )
	{	
		this->numEntitys += num;
	}
    void SetMass(int index, float m, float r,  Vector3 pos, Vector3 vel, Color4f light);

	void Game::SetNumBoxes( int num )
	{
		this->numEntitys += num;
	}

	void SetBox( int index, float m, Vector3 pos, Vector3 vel, Vector3 size, Vector3 angle, Vector3 angleVel, Color4f color );

	void Game::SetNumLines( int num )
	{
		this->numEntitys += num;	
	}

	void SetLine(int index, float m, float r, float h, Vector3 pos, Quaternion q, Color4f color);

	void SetGraviAcc(Vector3 graviAcc);

	void Update(float dt);
	void Draw();
	
	Vector3 GraviForce(int a, int b);
	virtual void release();							// delete the masses created;

	void SetNumEntities(int entities)
	{
		numEntitys = entities;
	}

	int GetNumEntities()
	{
		return numEntitys;
	}

	//Entity& GetEntity(int i)
 	//{
//		return Entities[i];
//	}

 	virtual void init();								// this method will call the init() method of every mass;
 	virtual void solve();							// no implementation because no forces are wanted in this basic container;
 	virtual void simulate(float dt);					// Iterate the masses by the change in time;
 	
private:
	//vector<Vector3> globalForces;
	int numEntitys;
	std::vector<Entity*> Entities;
	//list<Entity> Entities;
	Vector3 graviAcc;

	std::ofstream fileOut;
};
