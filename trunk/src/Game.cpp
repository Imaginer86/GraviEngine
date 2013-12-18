#include "Game.h"

#include "Entities\Mass.h"
#include "Entities\Box.h"
#include "Entities\Line.h"

 
void Game::SetNumMasses( int num )
{	
	this->numEntitys += num;
}


void Game::SetMass( int index, float m, float r, Vector3 pos, Vector3 vel, Color4f light )
{	
	Mass *mass = new Mass;
	mass->Set(m, r, pos, vel, light);
	Entities.push_back(mass);
}


void Game::SetNumBoxes( int num )
{
	this->numEntitys += num;
}


void Game::SetBox( int index, float m, Vector3 pos, Vector3 size, Vector3 angle, Color4f color )
{

	Box *box = new Box;
	box->SetMass(m);
	box->SetPos(pos);
	box->SetSize(size);
	box->SetAngle(angle);
	box->SetColor(color);
	Entities.push_back(box);
}


void Game::SetNumLines( int num )
{
	this->numEntitys += num;	
}

void Game::SetLine(int index, float m, float r, float h, Vector3 pos, Quaternion q, Color4f color)
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
	this->operate(dt);		
	//return;

// 	for(vector<Entity*>::iterator iter = Entities.begin(); iter != Entities.end(); iter++)
//  	{
//  		iter->init();
//  		iter->applyForce(this->graviForce);
//  		iter->simulateForce(dt);
//  		iter->simuleteAcc(this->graviAcc, dt);
//   
//  		iter->update(dt);
// 	}
 
 	for(vector<Entity*>::iterator iter1 = Entities.begin(); iter1 != Entities.end(); iter1++)
 		for(vector<Entity*>::iterator iter2 = Entities.begin(); iter2 != Entities.end(); iter2++)
 			if (iter1 != iter2)
 			{
 				Vector3 pos1 = (*iter1)->GetPos();
 				Vector3 pos2 = (*iter2)->GetPos();
 				float distance = (pos1 - pos2).length();
 				float rx = (*iter1)->GetR() + (*iter2)->GetR();
 				if (distance < rx)
 				{
 					Vector3 vel1 = (*iter1)->GetVel();
 					Vector3 vel2 = (*iter2)->GetVel();
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
		
		(*itera)->SetVel(Vector3(0.0f, 0.0f ,0.0f));
		(*iterb)->SetVel(Vector3(0.0f, 0.0f ,0.0f));
		
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
			if(itera != iterb) (*itera)->applyForce(GraviForce(a,b));
		}
	}
	// in advanced containers, this method will be overrided and some forces will act on masses
}

void Game::simulate( float dt ) /* Iterate the masses by the change in time */
{
	for(vector<Entity*>::iterator itera = Entities.begin(); itera != Entities.end(); itera++)		// We will iterate every mass
		(*itera)->simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
}

void Game::operate( float dt ) /* The complete procedure of simulation */
{
	init();										// Step 1: reset forces to zero
	solve();									// Step 2: apply forces
	simulate(dt);								// Step 3: iterate the masses by the change in time
}




void Game::release() /* delete the masses created */
{
	numEntitys = 0;
	Entities.clear();
}

