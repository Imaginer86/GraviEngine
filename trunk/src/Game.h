#pragma once
#include "Mass.h"
#include "Box.h"
#include "Line.h"
//#include <vector>

const float G = 0.01f;

//using namespace std;

class Game
{
public:
	Game(void);
	~Game(void);

	void SetNumMasses(int num);
    void SetMass(int index, float m, float r,  Vector3D pos, Vector3D vel, Color4f light);

	void SetNumBoxes(int num);
	void SetBox(int index, float m, Vector3D pos, Vector3D size, Vector3D angle, Color4f color);

	void SetNumLines(int num);
	void SetLine(int index, float m, float r, Vector3D pos1, Vector3D pos2, Color4f color);

	void SetGraviAcc(Vector3D graviAcc);


	void Update(float dt);
	void Draw();
	
	Vector3D GraviForce(int a, int b);
	virtual void release();							// delete the masses created;

 	virtual void init();								// this method will call the init() method of every mass;
 	virtual void solve();							// no implementation because no forces are wanted in this basic container;
 	virtual void simulate(float dt);					// Iterate the masses by the change in time;
 	virtual void operate(float dt);				// The complete procedure of simulation;


//private:
	int numMasses;								// number of masses in this container	
	Mass *masses;									// masses are held by pointer to pointer. (Here Mass** represents a 1 dimensional array)

	int numBoxs;
	Box *boxes;

	int numLines;
	Line *lines;

	//vector<Vector3D> globalForces;
	Vector3D graviAcc;

};
