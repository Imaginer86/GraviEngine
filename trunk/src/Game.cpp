#include "Game.h"
#include "Entities\Mass.h"
#include "Entities\Box.h"
//#include "Entities\Line.h"

#include <typeinfo.h>

static const float G = 0.01f;
static const float minDistG = 0.1f;


Game::Game()
: numEntitys(0)
//, Entities(null)
, graviAcc(0, 0, 0)
{
//		fileOut = std::ofstream("out.dat", std::ios::out);
}

Game::~Game()
{
	numEntitys = 0;
	for (unsigned i = 0; i < Entities.size(); i++)
		delete Entities[i];
	Entities.clear();
}

void Game::Release() /* delete the masses created */
{
	numEntitys = 0;
	for (unsigned i = 0; i < Entities.size(); i++)
		delete Entities[i];
	Entities.clear();
}

void Game::SetMass( float m, float r, Vector3 pos, Vector3 vel, Color4f color )
{	
	Mass* mass = new Mass;	
	mass->Set(m, r, pos, vel, color);
	Entities.push_back(mass);
}

void Game::SetBox(float m, Vector3 size, Vector3 pos, Vector3 vel, Quaternion q, Quaternion qVel, Color4f color)
{
	Box *box = new Box;	
	box->SetMass(m);
	box->SetPos(pos);
	box->SetVel(vel);
	box->SetSize(size);
	box->SetAngleQ(q);
	box->SetAngleVelQ(qVel);
	box->SetColor(color);
	Entities.push_back(box);
}

/*
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
*/



void Game::Collision(float dt)
{

	for (unsigned a = 0; a < Entities.size(); a++)
		for (unsigned b = 0; b < Entities.size(); b++)
			if (a != b)
			{
				if (typeid(*Entities[a]) == typeid(Mass) && typeid(*Entities[b]) == typeid(Mass))
				{
					Mass *ma = dynamic_cast<Mass*>(Entities[a]);
					Mass *mb = dynamic_cast<Mass*>(Entities[b]);
					float dist = (ma->GetPos() - mb->GetPos()).length();
					float r2 = ma->GetR() + mb->GetR();
					if (dist < r2)
					{
						float v = (ma->GetVel() - mb->GetVel()).length();
						float dc = (dist - r2) / v;
						if (dc <= 0.0f)
						{
							Vector3 p1 = ma->GetPos();
							Vector3 v1 = ma->GetVel();
							Vector3 p2 = mb->GetPos();
							Vector3 v2 = mb->GetVel();

							p1 = p1 + v1*dc;
							p2 = p2 + v2*dc;

							ma->SetPos(p1);
							mb->SetPos(p2);

							Vector3 p1p2 = p2 - p1;
							p1p2.unitize();
							Vector3 pn1 = p1p2*v1;
							//pn1.unitize();
							Vector3 v1t = Vector3(p1p2.x*pn1.x*pn1.x + p1p2.x*(pn1.x*pn1.y - pn1.z) + p1p2.x*(pn1.x*pn1.z + pn1.y),
								p1p2.y*(pn1.y*pn1.x + pn1.z) + p1p2.y*pn1.y*pn1.y + p1p2.y*(pn1.y*pn1.z - pn1.x),
								p1p2.z*(pn1.z*pn1.x - pn1.y) + p1p2.z*(pn1.z*pn1.y + pn1.x) + p1p2.z*pn1.z*pn1.z);
							float v1n = v1.dotProduct(p1p2);
							float v1ts = v1.dotProduct(v1t);


							Vector3 p2p1 = p1 - p2;
							p2p1.unitize();
							//p1p2 = - p1p2;
							Vector3 pn2 = p2p1*v2;
							//pn2.unitize();

							Vector3 v2t = Vector3(p2p1.x*pn2.x*pn2.x + p2p1.x*(pn2.x*pn2.y - pn2.z) + p2p1.x*(pn2.x*pn2.z + pn2.y),
								p2p1.y*(pn2.y*pn2.x + pn2.z) + p2p1.y*pn2.y*pn2.y + p2p1.y*(pn2.y*pn2.z - pn2.x),
								p2p1.z*(pn2.z*pn2.x - pn2.y) + p2p1.z*(pn2.z*pn2.y + pn2.x) + p2p1.z*pn2.z*pn2.z);

							float v2n = v2.dotProduct(p2p1);
							float v2ts = v2.dotProduct(v2t);


							float m1 = ma->GetMass();
							float m2 = mb->GetMass();


							Vector3 v11 = v1t - p1p2*v1n + ((p1p2*m1*v1n + p2p1*m2*v2n) / (m1 + m2))*2.0f;
							Vector3 v22 = v2t - p2p1*v2n + ((p1p2*m1*v1n + p2p1*m2*v2n) / (m1 + m2))*2.0f;

							//ma->SetPos(ma->GetPos() - ma->GetVel()*dt);
							//mb->SetPos(mb->GetPos() - mb->GetVel()*dt);

							ma->SetVel(v11);
							mb->SetVel(v22);

							ma->SetPos(p1 + v11*(dt + dc));
							mb->SetPos(p2 + v22*(dt + dc));


							dist = (ma->GetPos() - mb->GetPos()).length();
							r2 = ma->GetR() + mb->GetR();

							float t1 = v11.length() + v1.length();
							float t2 = v22.length() + v2.length();

							//ma->simulateForce(dt);
							//mb->simulateForce(dt);

							if (dist < r2)
							{
								int t = 0;
							}
						}
					}
				}

				if (typeid(*Entities[a]) == typeid(Mass) && typeid(*Entities[b]) == typeid(Box) || typeid(*Entities[a]) == typeid(Box) && typeid(*Entities[b]) == typeid(Mass))
				{
					Mass *mass;
					Box *box;
					if (typeid(*Entities[a]) == typeid(Mass) && typeid(*Entities[b]) == typeid(Box))
					{
						mass = dynamic_cast<Mass*>(Entities[a]);
						box = dynamic_cast<Box*>(Entities[b]);						
					}
					else if (typeid(*Entities[b]) == typeid(Mass) && typeid(*Entities[a]) == typeid(Box))
					{
						mass = dynamic_cast<Mass*>(Entities[b]);
						box = dynamic_cast<Box*>(Entities[a]);
					}
					Vector3 po = mass->GetPos();
					float ro = mass->GetR();
					Vector3 pb = box->GetPos();
					Quaternion q = box->GetAngleQ();
					//Vector3 axicb;
					//float angleb;
					//q.toAxisAngle(axicb, angleb);
					Vector3 size = box->GetSize();
					size /= 0.5f;

					Quaternion qn;
					qn.fromAxisAngle(size, 0.0f);

					Quaternion qs(qn *q);

					Vector3 pnx = qs.rotate(Vector3(po.x, 0.0f, 0.0f));
					Vector3 pny = qs.rotate(Vector3(0.0f, po.y, 0.0f));
					Vector3 pnz = qs.rotate(Vector3(0.0f, 0.0f, po.z));



					Vector3 pbxu = pb + pnx;
					Vector3 pbxd = pb - pnx;
					Vector3 pbyu = pb + pny;
					Vector3 pbyd = pb - pny;
					Vector3 pbzu = pb + pnz;
					Vector3 pbzd = pb - pnz;

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

	Vector3 Dif;
	float r;

	auto t =  Entities[a]->GetPos();

	Dif = Entities[a]->GetPos() - Entities[b]->GetPos();

 	r = Dif.length();
	
	f = Entities[b]->GetPos() - Entities[a]->GetPos();
	
	gforce = G * Entities[a]->GetMass() * Entities[b]->GetMass()/(r * r);
	
	if (r < minDistG)
	{
		gforce = 0;
		Vector3 vel0(0.0f, 0.0f ,0.0f);

		Entities[a]->SetVel(vel0);
		Entities[b]->SetVel(vel0);
		
		f.x = 0;
		f.y = 0;
		f.z = 0;
	}

	f *= gforce;

	return f;
}

void Game::Update(float dt)
{

	//static unsigned int iteration = 0;
	this->Init();										// Step 1: reset forces to zero
	//this->Solve();									// Step 2: apply forces
	this->AddGraviAcc(dt);
	this->Simulate(dt);								// Step 3: iterate the masses by the change in time

	//this->Collision(dt);

	return;
}

void Game::Init() /* this method will call the init() method of every mass */
{
	for(unsigned i = 0; i < Entities.size(); i++)		// We will init() every mass
		Entities[i]->init();						// call init() method of the mass
}

void Game::Solve() /* no implementation because no forces are wanted in this basic container */
{
	for(unsigned a = 0; a < Entities.size(); a++)
	{
		for(unsigned b = 0; b < Entities.size(); b++)
		{			
			if (a != b)
			{
				Vector3 force(GraviForce(a,b));
				Entities[a]->applyForce(force); //Gravi Force
			}
		}
	}
	// in advanced containers, this method will be overrided and some forces will act on masses
}

void Game::AddGraviAcc(float dt)
{
	for (unsigned i = 0; i < Entities.size(); i++)
		Entities[i]->applyAcc(graviAcc, dt);
}

void Game::Simulate( float dt ) /* Iterate the masses by the change in time */
{
	for(unsigned i = 0; i < Entities.size(); i++)		// We will iterate every mass
		Entities[i]->simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
}