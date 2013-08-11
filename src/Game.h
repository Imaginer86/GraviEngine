#pragma once
#include "Mass.h"

const double G = 0.01f;

class Game
{
public:
	Game(void);
	~Game(void);
	void Update(float eps);
	void Draw();

	int numOfMasses;								// number of masses in this container
	Mass *masses;									// masses are held by pointer to pointer. (Here Mass** represents a 1 dimensional array)
	float timeScale;

	    void SetSize(int num) {
        masses = new Mass[num];
        this->numOfMasses = num;
    }


    void SetMass(int index, double m, double r,  Vector3D pos, Vector3D vel, Color4f light) {
        masses[index].Set(m, r, pos, vel, light);
    }

	Vector3D GraviForce(int a, int b)
	{
		Vector3D f;
		double gforce;
		double x;
		double y;
		double z;
		double r;
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

	virtual void release()							// delete the masses created
	{
		/*for (int a = 0; a < numOfMasses; ++a)		// we will delete all of them
		{
			delete(masses[a]);
			masses[a] = NULL;
		}
			
		delete(masses);
		masses = NULL;
		*/
	}

	Mass getMass(int index)
	{
		if (index < 0 || index >= numOfMasses)		// if the index is not in the array
			return Mass();							// then return NULL

		return masses[index];						// get the mass at the index
	}

	virtual void init()								// this method will call the init() method of every mass
	{
		for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
			masses[a].init();						// call init() method of the mass
	}

	virtual void solve()							// no implementation because no forces are wanted in this basic container
	{
		for(int a = 0; a < numOfMasses; a++)
			for(int b = 0; b < numOfMasses; b++)
			{
				if(a!=b) masses[a].applyForce(GraviForce(a,b));
			}
													// in advanced containers, this method will be overrided and some forces will act on masses
	}



	virtual void simulate(double dt)					// Iterate the masses by the change in time
	{
		for (int a = 0; a < numOfMasses; ++a)		// We will iterate every mass
			masses[a].simulate(dt);				// Iterate the mass and obtain new position and new velocity
	}

	virtual void operate(double dt)					// The complete procedure of simulation
	{
		init();										// Step 1: reset forces to zero
		solve();									// Step 2: apply forces
		simulate(dt*this->timeScale);								// Step 3: iterate the masses by the change in time
	}

};
