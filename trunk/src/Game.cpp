#include "Game.h"

#include "Entities\Mass.h"
#include "Entities\Box.h"
#include "Entities\Line.h"

//#include <iostream>
//#include <fstream>

using namespace std;


Game::Game()
: numEntitys(0)
//, Entities(null)
, graviAcc(0, 0, 0)
{
//		fileOut = std::ofstream("out.dat", std::ios::out);
}

 

void Game::SetMass( float m, float r, Vector3 pos, Vector3 vel, Color4f light )
{	
	Mass* mass = new Mass;	
	mass->Set(m, r, pos, vel, light);
	Entities.push_back(mass);
}

void Game::SetBox( float m, Vector3 pos, Vector3 vel, Vector3 size, Vector3 angle, Vector3 angleVel, Color4f color )
{

	Box *box = new Box;	
	box->SetMass(m);
	box->SetPos(pos);
	box->SetVel(vel);
	box->SetSize(size);
	box->SetAngle(angle);
	box->SetAngleVel(angleVel);
	box->SetColor(color);
	Entities.push_back(box);
}

void Game::SetLine(float m, float r, float h, Vector3 pos, Quaternion q, Color4f color)
{
	Line *line = new Line;
	line->SetMass(m);
	line->SetR(r);
	line->SetH(h);
	line->SetPos(pos);
	//line->SetPos2(pos2);
	line->SetQuaternion(q);
	line->SetColor(color);
	Entities.push_back(line);
}

void Game::SetGraviAcc(Vector3 graviAcc)
{
	this->graviAcc = graviAcc;
}

void Game::Update( float dt )
{

	//static unsigned int iteration = 0;
	init();										// Step 1: reset forces to zero
	solve();									// Step 2: apply forces
	simulate(dt);								// Step 3: iterate the masses by the change in time

	return;

	//int a = 0;

	//int cc = 2;//

	
	//while (cc > 0)
	{
		for(vector<Entity*>::iterator itera = Entities.begin(); itera != Entities.end(); itera++)
		{
			int b = 0;
			for(vector<Entity*>::iterator iterb = Entities.begin(); iterb != Entities.end(); iterb++, b++)
			{
				if(itera != iterb)
					{

						/*try
						{
							Mass* a = static_cast<Mass*>(*itera);
							fileOut << iteration << std::ends << a << std::ends << typeid(*itera).name() << std::ends << typeid(a).name() << std::endl;
						}
						catch (const std::bad_cast& e)
						{
							fileOut << "Mass!!!" << typeid(a).name() << std::endl;
							fileOut << e.what() << std::endl;
							fileOut << "Этот объект не является объектом типа Mass" << std::endl;
						}*/

						//fileOut << typeid(**itera).name() << std::endl;
						if (typeid(**itera) == typeid(Mass) && typeid(**iterb) == typeid(Mass))
						{
							float t_colission = (*itera)->ProcessColisions(**iterb);
							if( t_colission < 0.f)
							{
								//(*itera)->c++;
								//(*iterb)->c++;

								(*itera)->Collision(**iterb);



								float t_colission = (*itera)->ProcessColisions(**iterb);

								

								//(*itera)->c--;
								//(*iterb)->c--;

								if (abs(t_colission) < 0.f)
								{

									this->Update(-t_colission);

									this->Draw();

									t_colission = (*itera)->ProcessColisions(**iterb);

									if (abs(t_colission) < 0.0025f)
									{
										int t = 0;
									}
									else
									{
										int t = 0;
									}
								}

								//(*itera)->c--;
								//(*iterb)->c--;


								
								//fileOut << "Collision" << iteration << std::ends << std::ends << typeid(**itera).name() << std::endl;
							}
						}
				}
			}
		}
		//cc--;
	}


	//iteration++;

	return;
}

void Game::Draw()
{
	for(int i = 0; i < GetNumEntities(); i++) {
		Entities[i]->Draw();
	}

}


Vector3 Game::GraviForce( int a, int b )
{
	Vector3 f;
	float gforce;
	float x;
	float y;
	float z;
	float r;
	vector<Entity*>::iterator itera = Entities.begin();
	for(int i = 0; i < a; i++)
		itera++;
	vector<Entity*>::iterator iterb = Entities.begin();
	for(int i = 0; i < b; i++)
		iterb++;

 	x = (*itera)->GetPos().x - (*iterb)->GetPos().x;
	y = (*itera)->GetPos().y - (*iterb)->GetPos().y;
	z = (*itera)->GetPos().z - (*iterb)->GetPos().z;

 	r = sqrt(x*x + y*y + z*z);
	
	f = (*iterb)->GetPos() - (*itera)->GetPos();
	
	gforce = G * (*itera)->GetMass() * (*iterb)->GetMass()/(r * r);
	
	if (r < 0.1)
	{
		gforce = 0;
		Vector3 vel0(0.0f, 0.0f ,0.0f);

		(*itera)->SetVel(vel0);
		(*iterb)->SetVel(vel0);
		
		f.x = 0;
		f.y = 0;
		f.z = 0;
	}

	f *= gforce;

	return f;
}




void Game::init() /* this method will call the init() method of every mass */
{
	for(vector<Entity*>::iterator iter = Entities.begin(); iter != Entities.end(); iter++)		// We will init() every mass
		(*iter)->init();						// call init() method of the mass
}

void Game::solve() /* no implementation because no forces are wanted in this basic container */
{
	int a = 0;
	for(vector<Entity*>::iterator itera = Entities.begin(); itera != Entities.end(); itera++, a++)
	{
		int b = 0;
		for(vector<Entity*>::iterator iterb = Entities.begin(); iterb != Entities.end(); iterb++, b++)
		{
			Vector3 force(GraviForce(a,b));
			if(itera != iterb) (*itera)->applyForce(force);
		}
	}
	// in advanced containers, this method will be overrided and some forces will act on masses
}

void Game::simulate( float dt ) /* Iterate the masses by the change in time */
{
	for(vector<Entity*>::iterator iter = Entities.begin(); iter != Entities.end(); iter++)		// We will iterate every mass
		(*iter)->simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
}





void Game::release() /* delete the masses created */
{
	numEntitys = 0;
	for(vector<Entity*>::iterator iter = Entities.begin(); iter != Entities.end(); iter++)
		delete *iter;
	Entities.clear();
}