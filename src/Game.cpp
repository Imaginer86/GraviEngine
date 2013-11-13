#include "Game.h"

Game::Game(void)
: numMasses(0)
, numBoxs(0)
, numLines(0)
, graviAcc(0, 0, 0)
{
}

Game::~Game(void)
{
	delete[] masses;
	delete[] boxes;
	delete[] lines;
}

void Game::SetNumMasses( int num )
{
	masses = new Mass[num];
	this->numMasses = num;
}

void Game::SetMass( int index, float m, float r, Vector3 pos, Vector3 vel, Color4f light )
{
	masses[index].Set(m, r, pos, vel, light);
}


void Game::SetNumBoxes( int num )
{
	this->boxes = new Box[num];
	this->numBoxs = num;
}


void Game::SetBox( int index, float m, Vector3 pos, Vector3 size, Vector3 angle, Color4f color )
{
	this->boxes[index].m = m;
	this->boxes[index].pos = pos;
	this->boxes[index].size = size;
	this->boxes[index].angle = angle;
	this->boxes[index].color = color;
}


void Game::SetNumLines( int num )
{
	this->numLines = num;
	this->lines = new Line[num];
}

void Game::SetLine(int index, float m, float r, Vector3 pos1, Vector3 pos2, Color4f color)
{
	this->lines[index].m = m;
	this->lines[index].r = r;
	this->lines[index].pos1 = pos1;
	this->lines[index].pos2 = pos2;
	this->lines[index].color = color;
}

void Game::SetGraviAcc(Vector3 graviAcc)
{
	this->graviAcc = graviAcc;
}

void Game::Update( float dt )
{
	this->operate(dt);


		
	//return;


	for(int i = 0; i < numMasses; i++)
	{
		//this->masses[i].init();
		//this->masses[i].applyForce(this->graviForce);
		//this->masses[i].simulateForce(dt);
		this->masses[i].simuleteAcc(this->graviAcc, dt);

		this->masses[i].update(dt);
	}

	for (int i = 0; i < numMasses; i++)
		for(int j = 0; j < numMasses; j++)
			if (i != j)
			{
				Vector3 pos1 = this->masses[i].pos;
				Vector3 pos2 = this->masses[j].pos;
				float distance = (pos1 - pos2).length();
				float rx = this->masses[i].r + this->masses[j].r;
				if (distance < rx)
				{
					Vector3 vel1 = this->masses[i].vel;
					Vector3 vel2 = this->masses[j].vel;
					Vector3 pos10 = pos1 + vel1*(-dt);
					Vector3 pos20 = pos2 + vel2*(-dt);
					float distance0 = (pos10 - pos20).length();
					float t = (distance0 - rx)/(vel1.length() + vel2.length());
					float mt = dt - t;
					if(t > dt)
						int a = 0;
				}
			}
	
}

void Game::Draw()
{

}


Vector3 Game::GraviForce( int a, int b )
{
	Vector3 f;
	float gforce;
	float x;
	float y;
	float z;
	float r;
	x = masses[a].pos.x-masses[b].pos.x;
	y = masses[a].pos.y-masses[b].pos.y;
	z = masses[a].pos.z-masses[b].pos.z;
	r= sqrt(x*x + y*y + z*z);

	f = masses[b].pos - masses[a].pos;

	gforce = G*masses[a].m*masses[b].m/(r*r);

	if (r < 0.1)
	{
		gforce = 0;
		/*
		masses[a].vel.x = 0;
		masses[a].vel.y = 0;
		masses[a].vel.z = 0;
		masses[b].vel.x = 0;
		masses[b].vel.y = 0;
		masses[b].vel.z = 0;
		*/

		f.x = 0;
		f.y = 0;
		f.z = 0;
	}


	f *= gforce;



	return f;
}




void Game::init() /* this method will call the init() method of every mass */
{
	for (int a = 0; a < numMasses; ++a)		// We will init() every mass
	masses[a].init();						// call init() method of the mass
}

void Game::solve() /* no implementation because no forces are wanted in this basic container */
{
	for(int a = 0; a < numMasses; a++)
	for(int b = 0; b < numMasses; b++)
	{
		if(a!=b) masses[a].applyForce(GraviForce(a,b));
	}
	// in advanced containers, this method will be overrided and some forces will act on masses
}

void Game::simulate( float dt ) /* Iterate the masses by the change in time */
{
	for (int a = 0; a < numMasses; ++a)		// We will iterate every mass
	masses[a].simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
}

void Game::operate( float dt ) /* The complete procedure of simulation */
{
	init();										// Step 1: reset forces to zero
	solve();									// Step 2: apply forces
	simulate(dt);								// Step 3: iterate the masses by the change in time
}




void Game::release() /* delete the masses created */
{
	numMasses = 0;
	delete [] masses;

	numBoxs = 0;
	delete [] boxes;

	numLines = 0;
	delete [] lines;
}

