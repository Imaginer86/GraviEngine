#include "Game.h"

#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo.h>

#include "../Sources/Core/Master.h"
#include "../Sources/Core/Camera.h"

#include "../Sources/Entities/Mass.h"
#include "../Sources/Entities/Box.h"
#include "../Sources/Entities/Smoke.h"
#include "../Sources/Entities/Sky.h"
#include "../Sources/Math/Math.h"
#include "../Sources/Math/Plane.h"

extern Color4f gLightAmbient;
extern Color4f gLightDiffuse;
extern Vector3 gLightPosition;

//unsigned Core::Master::gSceneNum;
//extern float64 gTimeScale;

static const float64  G = 6.673848;

static Sky mSky;

bool gUpdateCamera = false;
bool gFirstLoad = false;

Game::Game()
: numEntitys(0)
, bGraviMasses(false)
, bGraviAcc(false)
, bWindAcc(false)
, bCollisions(false)
, graviAcc(0, 0, 0)
{
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

void Game::AddMass( float64 m, float64 r, const Vector3& pos, const Vector3& vel, const Color4f& color )
{	
	Mass* mass = new Mass;	
	mass->Set(m, r, pos, vel, color);
	Entities.push_back(mass);
}

void Game::AddBox(float64 m, const Vector3& size, const Vector3& pos, const Vector3& vel, const Quaternion& q, const Quaternion& qVel, const Color4f& color)
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

void Game::AddSmoker(const Vector3& pos, const Vector3& rand, const Vector3& vel0, const Vector3& vel, const Color4f& color, unsigned long numEntitys)
{
	Smoke *smoke = new Smoke;
	smoke->Init(pos, rand, vel0, vel, color, numEntitys);
	Entities.push_back(smoke);
}

/*
void Game::SetLine(float64 m, float64 r, float64 h, Vector3 pos, Quaternion q, Color4f color)
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

void Game::Update(float64 dt)
{
	//static unsigned int iteration = 0;
	Init();										// Step 1: reset forces to zero	
	if (bGraviMasses)
	{
		Solve();									// Step 2: apply forces		
	}
	if (bGraviAcc)
	{
		AddGraviAcc(dt);		
	}
	if (bWindAcc)
	{
		AddWindAcc(dt);
	}
	if (bCollisions)
	{
		Collision(dt);
	}
	Simulate(dt);								// Step 3: iterate the masses by the change in time
}

void Game::Init() /* this method will call the init() method of every mass */
{
	for (unsigned i = 0; i < Entities.size(); i++)		// We will init() every mass
		Entities[i]->init();						// call init() method of the mass
}

void Game::AddGraviAcc(float64 dt)
{
	for (unsigned i = 0; i < Entities.size(); i++)
	{
		if (typeid(*Entities[i]) == typeid(Mass))
		{
			Entities[i]->applyAcc(graviAcc, dt);
		}
		if (typeid(*Entities[i]) == typeid(Smoke))
		{
			Entities[i]->applyAcc(graviAcc, dt);
			//Smoke* smoke = dynamic_cast<Smoke*>(Entities[i]);			
		}
	}
}

void Game::AddWindAcc(float64 dt)
{
	for (unsigned i = 0; i < Entities.size(); i++)
	{
		if (typeid(*Entities[i]) == typeid(Smoke))
		{
			Smoke* smoke = dynamic_cast<Smoke*>(Entities[i]);
			smoke->ApplyWind(dt);
		}
	}
}


void Game::Simulate(float64 dt) /* Iterate the masses by the change in time */
{
	for (unsigned i = 0; i < Entities.size(); i++)		// We will iterate every mass
		Entities[i]->simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
}


void Game::Collision(float64 dt)
{
	for (unsigned a = 0; a < (Entities.size() - 1); a++)
		for (unsigned b = a + 1; b < Entities.size(); b++)
			if (a != b)
			{
				if (typeid(*Entities[a]) == typeid(Mass) && typeid(*Entities[b]) == typeid(Mass))
				{
					Mass *ma = dynamic_cast<Mass*>(Entities[a]);
					Mass *mb = dynamic_cast<Mass*>(Entities[b]);
					float64 dist = (ma->GetPos() - mb->GetPos()).length();
					float64 r2 = ma->GetR() + mb->GetR();
					if (dist < r2)
					{
						float64 v = (ma->GetVel() - mb->GetVel()).length();
						float64 dc = (dist - r2) / v;
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
							float64 v1n = v1.dotProduct(p1p2);
							//float64 v1ts = v1.dotProduct(v1t);


							Vector3 p2p1 = p1 - p2;
							p2p1.unitize();
							//p1p2 = - p1p2;
							Vector3 pn2 = p2p1*v2;
							//pn2.unitize();

							Vector3 v2t = Vector3(p2p1.x*pn2.x*pn2.x + p2p1.x*(pn2.x*pn2.y - pn2.z) + p2p1.x*(pn2.x*pn2.z + pn2.y),
								p2p1.y*(pn2.y*pn2.x + pn2.z) + p2p1.y*pn2.y*pn2.y + p2p1.y*(pn2.y*pn2.z - pn2.x),
								p2p1.z*(pn2.z*pn2.x - pn2.y) + p2p1.z*(pn2.z*pn2.y + pn2.x) + p2p1.z*pn2.z*pn2.z);

							float64 v2n = v2.dotProduct(p2p1);
							//float64 v2ts = v2.dotProduct(v2t);


							float64 m1 = ma->GetMass();
							float64 m2 = mb->GetMass();


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

							//float64 t1 = v11.length() + v1.length();
							//float64 t2 = v22.length() + v2.length();

							//ma->simulateForce(dt);
							//mb->simulateForce(dt);

							if (dist < r2)
							{
								//int t = 0;
							}
						}
					}
				}

				if (typeid(*Entities[a]) == typeid(Mass) && typeid(*Entities[b]) == typeid(Box) || typeid(*Entities[a]) == typeid(Box) && typeid(*Entities[b]) == typeid(Mass))
				{
					Mass *mass = nullptr;
					Box *box = nullptr;
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
					Vector3 pm = mass->GetPos();
					float64 rm = mass->GetR();
					Vector3 vm = mass->GetVel();

					Vector3 pb = box->GetPos();
					Quaternion q = box->GetAngleQ();
					Vector3 axicb;
					float64 angleb;
					q.toAxisAngle(axicb, angleb);
					Quaternion q1;
					q1.fromAxisAngle(axicb, -angleb);
					Vector3 size = box->GetSize();
					size *= 0.5f;

					Vector3 diff = size;

					Vector3 P[8];
					P[0] = pb + Vector3(-diff.x, -diff.y, diff.z);;
					P[1] = pb + Vector3(-diff.x, -diff.y, -diff.z);
					P[2] = pb + Vector3(diff.x, -diff.y, -diff.z);
					P[3] = pb + Vector3(diff.x, -diff.y, diff.z);
					P[4] = pb + Vector3(-diff.x, diff.y, diff.z);
					P[5] = pb + Vector3(-diff.x, diff.y, -diff.z);
					P[6] = pb + Vector3(diff.x, diff.y, -diff.z);
					P[7] = pb + Vector3(diff.x, diff.y, diff.z);

					for (int i = 0; i < 8; i++)
					{
						Vector3 d = P[i] - pb;
						d = q1.rotate(d);
						P[i] = pb + d;
					}

					int PI[6][4] = {{0, 1, 2, 3}, {4, 7, 6, 5}, {0, 4, 5, 1}, {2, 6, 7, 3}, {0, 3, 7, 4}, {1, 5, 6, 2}};

					Plane PL[6];
					for (int i = 0; i < 6; i++)
						PL[i] = Plane(P[PI[i][0]], P[PI[i][1]], P[PI[i][2]]);

					for (int i = 0; i < 6; i++)
					{
						Vector3 pr = PL[i].proj(pm);
						//float64 t = PL[i].a*pr.x + PL[i].b*pr.y + PL[i].c*pr.z+PL[i].d;
						//float64 d = PL[i].distance(pm);
						float64 d = (pm - pr).length();
						//std::cout  << " distance i " << i << ": " << d << std::endl;
						if (d < rm)
						{
							//std::cout << "Collosion M (" << pm.x << ", " << pm.y << ", " << pm.z << ") and Plane " << i << std::endl;
							if (InterPlanePoint(pr, P[PI[i][0]], P[PI[i][1]], P[PI[i][2]], P[PI[i][3]]))
							{					
								Vector3 n(PL[i].a, PL[i].b, PL[i].c);
								n.unitize();
								Vector3 axic;
								axic = n*vm;
								
								if (axic.unitize() > Math::EPSILON)
								{

								
									float64 sina = abs(PL[i].a*vm.x + PL[i].b*vm.y + PL[i].c*vm.z)/(sqrt(PL[i].a*PL[i].a + PL[i].b*PL[i].b + PL[i].c*PL[i].c)*vm.length());
									float64 angle = 90.0 - Math::radiansToDegrees(asin(sina));
									Quaternion q;
									q.fromAxisAngle(axic, -2.0f*angle);
									q.normalize();
									//std::cout << "angle" << angle << std::endl;
									//std::cout << "    vm0 " << vm.x << " " << vm.y << " " << vm.z << " " << std::endl;									
									vm = q.rotate(vm);
									//std::cout << "    vm1 " << vm.x << " " << vm.y << " " << vm.z << " " << std::endl;
								}
								//else
								//{
									//vm = -vm;
								//}
								mass->SetVel(-vm);
							}
						}
					}

				}
			}
}

bool Game::InterPlanePoint(Vector3 pr, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3)
{
	Vector3 p10 = p1 - p0;
	Vector3 pm0 = pr - p0;
	float64 cosa = p10.dotProduct(pm0)/(p10.length()*pm0.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	Vector3 p21 = p2 - p1;
	Vector3 pm1 = pr - p1;
	cosa = p21.dotProduct(pm1)/(p21.length()*pm1.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	Vector3 p32 = p3 - p2;
	Vector3 pm2 = pr - p2;
	cosa = p32.dotProduct(pm2)/(p32.length()*pm2.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	Vector3 p03 = p0 - p3;
	Vector3 pm3 = pr - p3;
	cosa = p03.dotProduct(pm3)/(p03.length()*pm3.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	return true;
}


void Game::Draw()
{
	mSky.Draw();
	for(int i = 0; i < GetNumEntities(); i++) 
	{
		Entities[i]->Draw();
	}
}


Vector3 Game::GraviForce( int a, int b )
{
	Vector3 f;
	float64 gforce;

	Vector3 Dif;
	float64 r;

	Vector3 t =  Entities[a]->GetPos();

	Dif = Entities[a]->GetPos() - Entities[b]->GetPos();

 	r = Dif.length();
	
	f = Entities[b]->GetPos() - Entities[a]->GetPos();
	
	gforce = float64( G * double(Entities[a]->GetMass() * Entities[b]->GetMass()/(r * r))  );
	
	//if (r < minDistG)
	if (r < Math::EPSILON)
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


/* no implementation because no forces are wanted in this basic container */

void Game::Solve() 
{
	for(unsigned a = 0; a < Entities.size(); a++)
	{
		for(unsigned b = 0; b < Entities.size(); b++)
		{			
			if (a != b)
			{
				Vector3 force(GraviForce(a,b));
				//if ( force.unitize() > Math::EPSILON )
				//{
				Entities[a]->applyForce(force); //Gravi Force
				//}
			}
		}
	}
	// in advanced containers, this method will be overrided and some forces will act on masses
}

void Game::SetNumStars(unsigned long numStars, bool randomize /* = true */)
{
	if (randomize)
	{
		mSky.Randomize();
	}
	mSky.Init(numStars);
}

bool Game::LoadData(unsigned fileNum)
{
	
	SetSceneNum(fileNum);

	std::string fileNumstr = std::to_string(fileNum);
	std::string fileName = "data//data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);

	if (!dataFile.is_open())
		return false;

	float64 timeScale;
	dataFile >> timeScale;
	Core::Master::gTimeScale = timeScale;
	
	bool bGraviMasses;
	dataFile >> bGraviMasses;
	SetBGraviMasses(bGraviMasses);

	bool bGraviAcc;
	dataFile >> bGraviAcc;
	SetBGraviAcc(bGraviAcc);

	bool bWindAcc;
	dataFile >> bWindAcc;
	SetBWindAcc(bWindAcc);

	bool bCollisions;
	dataFile >> bCollisions;
	SetBCollisions(bCollisions);

	unsigned long numStars;
	dataFile >> numStars;
	if (numStars)
	{
		SetNumStars(numStars /*,false*/);
	}

	Vector3 cameraPos;
	Vector3 cameraAxic;
	float64 cameraAngle;

	dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z
		>> cameraAxic.x >> cameraAxic.y >> cameraAxic.z
		>> cameraAngle;
	dataFile >> gUpdateCamera;

	if (gUpdateCamera || gFirstLoad)
	{
		gFirstLoad = false;
		Core::Camera::Instance().SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		Core::Camera::Instance().SetQuaternion(q);
	}

	dataFile >> gLightAmbient.r >> gLightAmbient.g >> gLightAmbient.b >> gLightAmbient.a;
	dataFile >> gLightDiffuse.r >> gLightDiffuse.g >> gLightDiffuse.b >> gLightDiffuse.a;
	dataFile >> gLightPosition.x >> gLightPosition.y >> gLightPosition.z;

	//RenderGL::Instance().rLightAmbient = gLightAmbient;
	//RenderGL::Instance().rLightDiffuse = gLightDiffuse;
	//RenderGL::Instance().rLightPosition = gLightPosition;


	Vector3 graviAcc;

	dataFile >> graviAcc.x >> graviAcc.y >> graviAcc.z;
	SetGraviAcc(graviAcc);

	unsigned int numEntities = 0;

	dataFile >> numEntities;

	SetNumEntities(numEntities);

	int numMass = 0;

	dataFile >> numMass;

	for (int i = 0; i < numMass; i++)
	{
		float64 m = 0.0f, r = 0.0f;
		Vector3 pos, vel;
		//bool isLight = false;
		Color4f color(0.0f, 0.0f, 0.0f, 0.0f);
		dataFile >> m >> r
			>> pos.x >> pos.y >> pos.z
			>> vel.x >> vel.y >> vel.z
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		AddMass(m, r, pos, vel, /*isLight,*/ color);
	}

	int numBoxs = 0;
	dataFile >> numBoxs;

	for (int i = 0; i < numBoxs; i++)
	{
		float64 m = 0.0;
		Vector3 pos, size, vel;
		Color4f color;
		Quaternion q;
		Quaternion qVel;
		float64 angle, angleVel;
		Vector3 angleAxic, angleVelAxic;
		dataFile >> m
			>> size.x >> size.y >> size.z
			>> pos.x >> pos.y >> pos.z
			>> vel.x >> vel.y >> vel.z
			>> q.x >> q.y >> q.z >> angle
			>> qVel.x >> qVel.y >> qVel.z >> angleVel
			>> color.r >> color.g >> color.b >> color.a;
		angle = Math::degreesToRadians(angle);
		angleVel = Math::degreesToRadians(angleVel);
		q.w = cos(angle / 2.0f);
		q.x *= sin(angle / 2.0f);
		q.y *= sin(angle / 2.0f);
		q.z *= sin(angle / 2.0f);

		qVel.w = cos(angleVel / 2.0f);
		qVel.x *= sin(angleVel / 2.0f);
		qVel.y *= sin(angleVel / 2.0f);
		qVel.z *= sin(angleVel / 2.0f);

		AddBox(m, size, pos, vel, q, qVel, color);
	}

	unsigned numSmokers = 0;
	unsigned long numParticless = 0;
	Vector3 pos;
	Vector3 rand;
	Vector3 vel0;
	Vector3 vel;
	Color4f color;
	dataFile >> numSmokers ;
	for (unsigned i = 0; i < numSmokers; i++)
	{
		dataFile >> numParticless
		>> pos.x >> pos.y >> pos.z
		>> rand.x >> rand.y >> rand.z
		>> vel0.x >> vel0.y >> vel0.z
		>> vel.x >> vel.y >> vel.z
		>> color.r >> color.g >> color.b >> color.a;

		AddSmoker( pos, rand, vel0, vel, color, numParticless);
	}

	/*	
	int numLines = 0;
	//dataFile >> numLines;
	//Game::Instance().SetNumLines(numLines);
	for(int i = 0; i < numLines; i++)
	{
	float64 m = 0.0f, r = 0.0f, h = 0.0f;
	Vector3 pos;
	Color4f color;
	Quaternion q;
	Vector3 u;
	float64 w = 0.0f;
	dataFile >> m >> r >> h
	>> pos.x >> pos.y >> pos.z
	>> u.x >> u.y >> u.z >> w
	>> color.r >> color.g >> color.b >> color.a;
	q.fromAxisAngle(u, w);
	Game::Instance().SetLine(m, r, h, pos, q, color);
	}
	*/
	

	dataFile.close();
	return true;
}