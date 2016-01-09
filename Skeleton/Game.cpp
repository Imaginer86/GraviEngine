#include "Game.h"

#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo.h>

#include "../../Sources/Constans.h"

#include "../../Sources/Math/Math.h"
#include "../../Sources/Math/Plane.h"
#include "../../Sources/Math/Random.h"

#include "../../Sources/Core/Master.h"
#include "../../Sources/Core/Camera.h"

#include "../../Sources/Entity/Mass.h"
#include "../../Sources/Entity/Box.h"
#include "../../Sources/Entity/Smoke.h"
#include "../../Sources/Entity/Sky.h"

using namespace Math;


//extern Color4f gLightAmbient;
//extern Color4f gLightDiffuse;
//extern Vector3f gLightPosition;

//unsigned Core::Master::gSceneNum;
//extern float32 gTimeScale;

//extern bool gFirstLoad;

unsigned countAddEntities = 0;

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
}

void Game::Release() /* delete the masses created */
{
	for (unsigned i = 0; i < numEntitys; ++i)
	{
		delete Entities[i];
	}

	numEntitys = 0;
	numMasses = 0;
	numBoxes = 0;
	numSmokers = 0;

	countAddEntities = 0;
	Entities = nullptr;

	mSky->Release();
	delete mSky;
}

void Game::SetNumEntities(unsigned numEntities_)
{
	numEntitys = numEntities_;
	//for (unsigned i = 0; i < numEntitys; ++i)
	//{
		//Entities[i] = new Entity;
	//}
	Entities = new Entity*[numEntitys];
}


void Game::AddMass( float32 m, float32 r, const Vector3f& pos, const Vector3f& vel, const Color4f& color )
{	
	Mass* mass = new Mass;	
	mass->Set(m, r, pos, vel, color);
	Entities[countAddEntities] = mass;
	++countAddEntities;
}

void Game::AddBox(float32 m, const Vector3f& size, const Vector3f& pos, const Vector3f& vel, const Quaternion& q, const Quaternion& qVel, const Color4f& color)
{
	Box *box = new Box;	
	box->SetMass(m);
	box->SetPos(pos);
	box->SetVel(vel);
	box->SetSize(size);
	box->SetAngleQ(q);
	box->SetAngleVelQ(qVel);
	box->SetColor(color);
	Entities[countAddEntities] = box;
	++countAddEntities;
}

void Game::AddSmoker(const Vector3f& pos, const Vector3f& rand, const Vector3f& vel0, const Vector3f& vel, const Color4f& color, unsigned numEntitys, bool createCollision)
{
	Smoke *smoke = new Smoke;
	smoke->Init(1.0f, pos, rand, vel0, vel, color, numEntitys, createCollision);
	Entities[countAddEntities] = smoke;
	++countAddEntities;
}

/*
void Game::SetLine(float32 m, float32 r, float32 h, Vector3 pos, Quaternion q, Color4f color)
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

void Game::Update(float32 dt)
{
	//static unsigned iteration = 0;
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
	for (unsigned i = 0; i < numEntitys; i++)		// We will init() every mass
		Entities[i]->init();						// call init() method of the mass
}

void Game::AddGraviAcc(float32 dt)
{
	for (unsigned i = 0; i < numEntitys; i++)
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

void Game::AddWindAcc(float32 dt)
{
	for (unsigned i = 0; i < numEntitys; i++)
	{
		if (typeid(*Entities[i]) == typeid(Smoke))
		{
			Smoke* smoke = dynamic_cast<Smoke*>(Entities[i]);
			smoke->ApplyWind(dt);
		}
	}
}


void Game::Simulate(float32 dt) /* Iterate the masses by the change in time */
{
	for (unsigned i = 0; i < numEntitys; i++)		// We will iterate every mass
		Entities[i]->simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
}


void Game::Collision(float32 dt)
{
	for (unsigned a = 0; a < (numEntitys - 1); a++)
		for (unsigned b = a + 1; b < numEntitys; b++)
			if (a != b)
			{
				if (typeid(*Entities[a]) == typeid(Mass) && typeid(*Entities[b]) == typeid(Mass))
				{
					Mass *ma = dynamic_cast<Mass*>(Entities[a]);
					Mass *mb = dynamic_cast<Mass*>(Entities[b]);
					float32 dist = (ma->GetPos() - mb->GetPos()).length();
					float32 r2 = ma->GetR() + mb->GetR();
					if (dist < r2)
					{
						float32 v = (ma->GetVel() - mb->GetVel()).length();
						float32 dc = (dist - r2) / v;
						if (dc <= 0.0f)
						{
							Vector3f p1 = ma->GetPos();
							Vector3f v1 = ma->GetVel();
							Vector3f p2 = mb->GetPos();
							Vector3f v2 = mb->GetVel();

							p1 = p1 + v1*dc;
							p2 = p2 + v2*dc;

							ma->SetPos(p1);
							mb->SetPos(p2);

							Vector3f p1p2 = p2 - p1;
							p1p2.unitize();
							Vector3f pn1 = p1p2*v1;
							//pn1.unitize();
							Vector3f v1t = Vector3f(p1p2.x*pn1.x*pn1.x + p1p2.x*(pn1.x*pn1.y - pn1.z) + p1p2.x*(pn1.x*pn1.z + pn1.y),
								p1p2.y*(pn1.y*pn1.x + pn1.z) + p1p2.y*pn1.y*pn1.y + p1p2.y*(pn1.y*pn1.z - pn1.x),
								p1p2.z*(pn1.z*pn1.x - pn1.y) + p1p2.z*(pn1.z*pn1.y + pn1.x) + p1p2.z*pn1.z*pn1.z);
							float32 v1n = v1.dotProduct(p1p2);
							//float32 v1ts = v1.dotProduct(v1t);


							Vector3f p2p1 = p1 - p2;
							p2p1.unitize();
							//p1p2 = - p1p2;
							Vector3f pn2 = p2p1*v2;
							//pn2.unitize();

							Vector3f v2t = Vector3f(p2p1.x*pn2.x*pn2.x + p2p1.x*(pn2.x*pn2.y - pn2.z) + p2p1.x*(pn2.x*pn2.z + pn2.y),
								p2p1.y*(pn2.y*pn2.x + pn2.z) + p2p1.y*pn2.y*pn2.y + p2p1.y*(pn2.y*pn2.z - pn2.x),
								p2p1.z*(pn2.z*pn2.x - pn2.y) + p2p1.z*(pn2.z*pn2.y + pn2.x) + p2p1.z*pn2.z*pn2.z);

							float32 v2n = v2.dotProduct(p2p1);
							//float32 v2ts = v2.dotProduct(v2t);


							float32 m1 = ma->GetMass();
							float32 m2 = mb->GetMass();


							Vector3f v11 = v1t - p1p2*v1n + ((p1p2*m1*v1n + p2p1*m2*v2n) / (m1 + m2))*2.0f;
							Vector3f v22 = v2t - p2p1*v2n + ((p1p2*m1*v1n + p2p1*m2*v2n) / (m1 + m2))*2.0f;

							//ma->SetPos(ma->GetPos() - ma->GetVel()*dt);
							//mb->SetPos(mb->GetPos() - mb->GetVel()*dt);

							ma->SetVel(v11);
							mb->SetVel(v22);

							ma->SetPos(p1 + v11*(dt + dc));
							mb->SetPos(p2 + v22*(dt + dc));


							dist = (ma->GetPos() - mb->GetPos()).length();
							r2 = ma->GetR() + mb->GetR();

							//float32 t1 = v11.length() + v1.length();
							//float32 t2 = v22.length() + v2.length();

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
					Vector3f pm = mass->GetPos();
					float32 rm = mass->GetR();
					Vector3f vm = mass->GetVel();

					Vector3f pb = box->GetPos();
					Quaternion q = box->GetAngleQ();
					Vector3f axicb;
					float32 angleb;
					q.toAxisAngle(axicb, angleb);
					Quaternion q1;
					q1.fromAxisAngle(axicb, -angleb);
					Vector3f size = box->GetSize();
					size *= 0.5f;

					Vector3f diff = size;

					Vector3f P[8];
					P[0] = pb + Vector3f(-diff.x, -diff.y, diff.z);;
					P[1] = pb + Vector3f(-diff.x, -diff.y, -diff.z);
					P[2] = pb + Vector3f(diff.x, -diff.y, -diff.z);
					P[3] = pb + Vector3f(diff.x, -diff.y, diff.z);
					P[4] = pb + Vector3f(-diff.x, diff.y, diff.z);
					P[5] = pb + Vector3f(-diff.x, diff.y, -diff.z);
					P[6] = pb + Vector3f(diff.x, diff.y, -diff.z);
					P[7] = pb + Vector3f(diff.x, diff.y, diff.z);

					for (int i = 0; i < 8; i++)
					{
						Vector3f d = P[i] - pb;
						d = q1.rotate(d);
						P[i] = pb + d;
					}

					int PI[6][4] = {{0, 1, 2, 3}, {4, 7, 6, 5}, {0, 4, 5, 1}, {2, 6, 7, 3}, {0, 3, 7, 4}, {1, 5, 6, 2}};

					Plane PL[6];
					for (int i = 0; i < 6; i++)
						PL[i] = Plane(P[PI[i][0]], P[PI[i][1]], P[PI[i][2]]);

					for (int i = 0; i < 6; i++)
					{
						Vector3f pr = PL[i].proj(pm);
						//float32 t = PL[i].a*pr.x + PL[i].b*pr.y + PL[i].c*pr.z+PL[i].d;
						//float32 d = PL[i].distance(pm);
						float32 d = (pm - pr).length();
						//std::cout  << " distance i " << i << ": " << d << std::endl;
						if (d < rm)
						{
							//std::cout << "Collosion M (" << pm.x << ", " << pm.y << ", " << pm.z << ") and Plane " << i << std::endl;
							if (InterPlanePoint(pr, P[PI[i][0]], P[PI[i][1]], P[PI[i][2]], P[PI[i][3]]))
							{					
								Vector3f n(PL[i].a, PL[i].b, PL[i].c);
								n.unitize();
								Vector3f axic;
								axic = n*vm;
								
								if (axic.unitize() > Math::EPSILON)
								{

								
									float32 sina = abs(PL[i].a*vm.x + PL[i].b*vm.y + PL[i].c*vm.z)/(sqrt(PL[i].a*PL[i].a + PL[i].b*PL[i].b + PL[i].c*PL[i].c)*vm.length());
									float32 angle = 90.0f - Math::radiansToDegrees(asin(sina));
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

bool Game::InterPlanePoint(Vector3f pr, Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3)
{
	Vector3f p10 = p1 - p0;
	Vector3f pm0 = pr - p0;
	float32 cosa = p10.dotProduct(pm0)/(p10.length()*pm0.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	Vector3f p21 = p2 - p1;
	Vector3f pm1 = pr - p1;
	cosa = p21.dotProduct(pm1)/(p21.length()*pm1.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	Vector3f p32 = p3 - p2;
	Vector3f pm2 = pr - p2;
	cosa = p32.dotProduct(pm2)/(p32.length()*pm2.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	Vector3f p03 = p0 - p3;
	Vector3f pm3 = pr - p3;
	cosa = p03.dotProduct(pm3)/(p03.length()*pm3.length());
	if ( cosa < 0.0f || cosa > 1.0f)
		return false;
	return true;
}


void Game::Draw()
{
	mSky->Draw();
	for(unsigned i = 0; i < numEntitys; i++) 
	{
		Entities[i]->Draw();
	}
}


Vector3f Game::GraviForce( int a, int b )
{
	Vector3f f;
	float32 gforce;

	Vector3f Dif;
	float32 r;

	Vector3f t =  Entities[a]->GetPos();

	Dif = Entities[a]->GetPos() - Entities[b]->GetPos();

 	r = Dif.length();
	
	f = Entities[b]->GetPos() - Entities[a]->GetPos();
	
	gforce = float32( G * double(Entities[a]->GetMass() * Entities[b]->GetMass()/(r * r))  );
	
	//if (r < minDistG)
	if (r < Math::EPSILON)
	{
		gforce = 0;
		Vector3f vel0(0.0f, 0.0f ,0.0f);

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
	for(unsigned a = 0; a < numEntitys; a++)
	{
		for(unsigned b = 0; b < numEntitys; b++)
		{			
			if (a != b)
			{
				Vector3f force(GraviForce(a,b));
				//if ( force.unitize() > Math::EPSILON )
				//{
				Entities[a]->applyForce(force); //Gravi Force
				//}
			}
		}
	}
	// in advanced containers, this method will be overrided and some forces will act on masses
}

void Game::SetNumStars(unsigned numStars, bool randomize /* = true */)
{
	mSky = new Sky;


	if (randomize)
	{
		mSky->Randomize();
	}
	mSky->Init(numStars);
}

bool Game::SaveData(const std::string& fileName)
{
	std::ofstream dataFile(fileName, std::ios::out);

	if (!dataFile.is_open())
		return false;

	char space = ' ';
	float32 timeScale = Core::Master::Instance().gTimeScale;
	dataFile << timeScale << std::endl;

	unsigned UPF, FPS, UPS;
	UPF = Core::Master::Instance().UPF, FPS = Core::Master::Instance().gfps, UPS = Core::Master::Instance().gups;
	dataFile << UPF << space << FPS << space << UPS << space << std::endl;
	
	bool bGraviMasses = GetBGraviMasses();
	dataFile << bGraviMasses << std::endl;

	bool bGraviAcc = GetBGraviAcc();
	dataFile << bGraviAcc << std::endl;

	bool bWindAcc = GetBWindAcc();
	dataFile << bWindAcc << std::endl;

	bool bCollisions = GetBCollisions();
	dataFile << bCollisions << std::endl;
	
	Vector3f cameraPos = Core::Camera::Instance().GetPos();
	Vector3f cameraAxic;
	float32 cameraAngle;
	Core::Camera::Instance().GetQuaternion().toAxisAngle(cameraAxic, cameraAngle);
	
	dataFile << cameraPos.x << space << cameraPos.y << space << cameraPos.z << space << std::endl
		<< cameraAxic.x << space << cameraAxic.y << space << cameraAxic.z << space << cameraAngle << std::endl;
	dataFile << Core::Master::Instance().gUpdateCamera << std::endl;

	Core::Master master = Core::Master::Instance();
	dataFile << master.gLightAmbient.r << space << master.gLightAmbient.g << space << master.gLightAmbient.b << space << master.gLightAmbient.a << space << std::endl;
	dataFile << master.gLightDiffuse.r << space << master.gLightDiffuse.g << space << master.gLightDiffuse.b << space << master.gLightDiffuse.a << space << std::endl;
	dataFile << master.gLightPosition.x << space << master.gLightPosition.y << space << master.gLightPosition.z << space << std::endl;

	Vector3f graviAcc = GetGraviAcc();

	dataFile << graviAcc.x << space << graviAcc.y << space << graviAcc.z << space << std::endl;

	unsigned numStars = GetNumStars();
	dataFile << numStars << std::endl;
	
	unsigned numEntities = GetNumEntities();;

	dataFile << numEntities << std::endl;

	int numMass = GetNumMasses();	
	dataFile << numMass << std::endl;

	int numBoxs = GetNumBoxes();
	dataFile << numBoxs << std::endl;

	unsigned numSmokers = GetNumSmokers();	
	dataFile << numSmokers << std::endl;
	
	float32 m;
	float32 r;
	Vector3f pos;
	Vector3f vel;		
	Color4f color;

	unsigned i = 0;
	for (i; i < numMasses; ++i)
	{
		Mass* M = dynamic_cast<Mass*>(Entities[i]);

		m = M->GetMass();
		r = M->GetR();
		pos = M->GetPos();
		vel = M->GetVel();		
		color = M->GetColor();
		
		dataFile << m << std::endl
			<< r << std::endl
			<< pos.x << space << pos.y << space << pos.z << std::endl
			<< vel.x << space << vel.y << space << vel.z << std::endl
			//<< isLight
			<< color.r << space << color.g << space << color.b << space << color.a << std::endl;
	}
	for(i; i < numBoxes; ++i)
	{
		Box* B = dynamic_cast<Box*>(Entities[i]);

		m = B->GetMass();
		Vector3f size = B->GetSize();
		pos = B->GetPos();
		vel = B->GetVel();
		color = B->GetColor();
		Quaternion q = B->GetAngleQ();
		Vector3f angleAxic;
		float32 angle;
		q.toAxisAngle(angleAxic, angle);
		Quaternion qVel = B->GetAngleVelQ();
		Vector3f angleVelAxic;
		float32 angleVel;
		qVel.toAxisAngle(angleVelAxic, angleVel);
				
		dataFile << m << std::endl
			<< size.x << space << size.y << space << size.z << std::endl
			<< pos.x << space << pos.y << space << pos.z << std::endl
			<< vel.x << space << vel.y << space << vel.z << std::endl
			<< q.x << space << q.y << space << q.z << space << angle << std::endl
			<< qVel.x << space << qVel.y << space << qVel.z << space << angleVel << std::endl
			<< color.r << space << color.g << space << color.b << space << color.a << std::endl;
	}
	for (i; i < numSmokers; ++i)
	{
		Smoke* S = dynamic_cast<Smoke*>(Entities[i]);

		pos = S->GetPos();		
		Vector3f vel0 = S->GetVel0();
		vel = S->GetVel();
		color = S->GetColor();
		Vector3f rand( Random::Instance().randf(-1.0f, 1.0f), Random::Instance().randf(-1.0f, 1.0f), Random::Instance().randf(-1.0f, 1.0f));
		unsigned numParticless = S->GetNumParticles();
		
		bool createCollision = S->GetCreateCollision();

		dataFile << numParticless
			<< createCollision
			<< pos.x << space << pos.y << space << pos.z
			<< rand.x << space << rand.y << space << rand.z
			<< vel0.x << space << vel0.y << space << vel0.z
			<< vel.x << space << vel.y << space << vel.z
			<< color.r << space << color.g << space << color.b << color.a;
	}
	

	dataFile.close();
	return true;
}

bool Game::LoadData(const std::string& fileName)
{
	SetSceneName(fileName);

	std::ifstream dataFile(fileName, std::ios::in);

	if (!dataFile.is_open())
		return false;

	float32 timeScale;
	dataFile >> timeScale;
	Core::Master::Instance().gTimeScale = timeScale;

	unsigned UPF, FPR, UPR;
	dataFile >> UPF>> FPR >> UPR;
	Core::Master::Instance().UPF = UPF, Core::Master::Instance().FPR = FPR, Core::Master::Instance().UPR = UPR;
	
	bool bGraviMasses_;
	dataFile >> bGraviMasses_;
	SetBGraviMasses(bGraviMasses_);

	bool bGraviAcc_;
	dataFile >> bGraviAcc_;
	SetBGraviAcc(bGraviAcc_);

	bool bWindAcc_;
	dataFile >> bWindAcc_;
	SetBWindAcc(bWindAcc_);

	bool bCollisions_;
	dataFile >> bCollisions_;
	SetBCollisions(bCollisions_);

	Vector3f cameraPos;
	Vector3f cameraAxic;
	float32 cameraAngle;

	dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z
		>> cameraAxic.x >> cameraAxic.y >> cameraAxic.z
		>> cameraAngle;
	dataFile >> Core::Master::Instance().gUpdateCamera;

	if (Core::Master::Instance().gUpdateCamera || Core::Master::Instance().gFirstLoad)
	{
		Core::Master::Instance().gFirstLoad = false;
		Core::Camera::Instance().SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		Core::Camera::Instance().SetQuaternion(q);
	}

	Core::Master master = Core::Master::Instance();
	dataFile >> master.gLightAmbient.r >> master.gLightAmbient.g >> master.gLightAmbient.b >> master.gLightAmbient.a;
	dataFile >> master.gLightDiffuse.r >> master.gLightDiffuse.g >> master.gLightDiffuse.b >> master.gLightDiffuse.a;
	dataFile >> master.gLightPosition.x >> master.gLightPosition.y >> master.gLightPosition.z;

	//RenderGL::Instance().rLightAmbient = gLightAmbient;
	//RenderGL::Instance().rLightDiffuse = gLightDiffuse;
	//RenderGL::Instance().rLightPosition = gLightPosition;


	Vector3f graviAcc_;

	dataFile >> graviAcc_.x >> graviAcc_.y >> graviAcc_.z;
	SetGraviAcc(graviAcc_);

	unsigned numStars_;
	dataFile >> numStars_;
	SetNumStars(numStars_ /*,false*/);
	
	unsigned numEntities_;
	dataFile >> numEntities_;

	SetNumEntities(numEntities_);

	unsigned numMasses_;
	dataFile >> numMasses_;
	SetNumMasses(numMasses_);

	unsigned numBoxes_;
	dataFile >> numBoxes_;
	SetNumBoxes(numBoxes_);

	unsigned numSmokers_;
	dataFile >> numSmokers_;
	SetNumSmokers(numSmokers_);

	for (unsigned i = 0; i < numMasses; i++)
	{
		float32 m = 0.0f, r = 0.0f;
		Vector3f pos, vel;
		//bool isLight = false;
		Color4f color(0.0f, 0.0f, 0.0f, 0.0f);
		dataFile >> m >> r
			>> pos.x >> pos.y >> pos.z
			>> vel.x >> vel.y >> vel.z
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		AddMass(m, r, pos, vel, /*isLight,*/ color);
	}

	for (unsigned i = 0; i < numBoxes; i++)
	{
		float32 m = 0.0;
		Vector3f pos, size, vel;
		Color4f color;
		Quaternion q;
		Quaternion qVel;
		float32 angle, angleVel;
		Vector3f angleAxic, angleVelAxic;
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

	unsigned numParticless = 0;
	Vector3f pos;
	Vector3f rand;
	Vector3f vel0;
	Vector3f vel;
	Color4f color;
	bool createCollision;
	
	for (unsigned i = 0; i < numSmokers; i++)
	{
		dataFile >> numParticless
		>> createCollision
		>> pos.x >> pos.y >> pos.z
		>> rand.x >> rand.y >> rand.z
		>> vel0.x >> vel0.y >> vel0.z
		>> vel.x >> vel.y >> vel.z
		>> color.r >> color.g >> color.b >> color.a;

		AddSmoker( pos, rand, vel0, vel, color, numParticless, createCollision);
	}

	/*	
	int numLines = 0;
	//dataFile >> numLines;
	//Game::Instance().SetNumLines(numLines);
	for(int i = 0; i < numLines; i++)
	{
	float32 m = 0.0f, r = 0.0f, h = 0.0f;
	Vector3 pos;
	Color4f color;
	Quaternion q;
	Vector3 u;
	float32 w = 0.0f;
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