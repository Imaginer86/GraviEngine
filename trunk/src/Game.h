#pragma once
//#include <list>
#include <vector>

using namespace std;

#include "Entity.h"
//#include "Mass.h"
//#include "Box.h"
//#include "Line.h"


const float G = 0.01f;



class Game
{
public:
	Game()
	: numEntitys(0)
	, Entities(NULL)
	, graviAcc(0, 0, 0)
	{				
	}

	~Game(void){}
	

	void SetNumMasses(int num);
    void SetMass(int index, float m, float r,  Vector3 pos, Vector3 vel, Color4f light);

	void SetNumBoxes(int num);
	void SetBox(int index, float m, Vector3 pos, Vector3 size, Vector3 angle, Color4f color);

	void SetNumLines(int num);
	void SetLine(int index, float m, float r, Vector3 pos1, Vector3 pos2, Color4f color);

	void SetGraviAcc(Vector3 graviAcc);


	void Update(float dt);
	void Draw();
	
	Vector3 GraviForce(int a, int b);
	virtual void release();							// delete the masses created;

	int GetNumEntities()
	{
		return numEntitys;
	}

	Entity *GetEntity(int i)
 	{
		return Entities[i];
	}

 	virtual void init();								// this method will call the init() method of every mass;
 	virtual void solve();							// no implementation because no forces are wanted in this basic container;
 	virtual void simulate(float dt);					// Iterate the masses by the change in time;
 	virtual void operate(float dt);				// The complete procedure of simulation;


private:

	//vector<Vector3> globalForces;
	int numEntitys;
	vector<Entity*> Entities;
	//list<Entity> Entities;
	Vector3 graviAcc;
};
