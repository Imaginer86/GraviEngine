#pragma once
#include <vector>
#include "Entities\Entity.h"
#include "Math\Quaternion.h"

const float G = 0.01f;

class Game
{
public:
	Game();

	virtual ~Game(void)
	{
//		fileOut.close();
	}	

	void SetNumEntities(int entities)
	{
		numEntitys = entities;
	}

	int GetNumEntities()
	{
		return numEntitys;
	}

	void Game::SetNumMasses( int num )
	{	
		this->numEntitys += num;
	}
    void SetMass(float m, float r,  Vector3 pos, Vector3 vel, Color4f light);

	void Game::SetNumBoxes( int num )
	{
		this->numEntitys += num;
	}

	void SetBox(float m, Vector3 pos, Vector3 vel, Vector3 size, Vector3 angle, Vector3 angleVel, Color4f color );

	void Game::SetNumLines( int num )
	{
		this->numEntitys += num;	
	}

	void SetLine(float m, float r, float h, Vector3 pos, Quaternion q, Color4f color);

	void SetGraviAcc(Vector3 graviAcc);

	void Update(float dt);
	void Draw();
	
	Vector3 GraviForce(int a, int b);
	virtual void release();							// delete the masses created;

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

//	std::ofstream fileOut;
};
