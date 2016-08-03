#include "Game.h"

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <typeinfo>


#include "Constans.h"

#include "Math/Math.h"
#include "Math/Plane.h"
#include "Math/Random.h"

#include "Core/Master.h"
#include "Core/Camera.h"
#include "Core/Node.h"
#include "Core/FileStream.h"

#include "Physics/Sphere.h"
#include "Physics/Plane.h"
#include "Physics/Box.h"
#include "Physics/Smoke.h"
#include "Physics/Shape.h"
#include "Physics/Video.h"
//#include "Physics/Sky.h"

void Game::Init() /* this method will call the init() method of every mass */
{	
	for (unsigned i = 0; i < numEntitys; i++)		// We will init() every mass
		Entities[i]->init();						// call init() method of the mass
}

void Game::Release() /* delete the masses created */
{
	for (unsigned i = 0; i < numEntitys; ++i)
	{
		delete Entities[i];
	}

	numEntitys = 0;
	numSpherees = 0;
	numBoxes = 0;
	numSmokers = 0;

	countAddEntities = 0;
	Entities = nullptr;

	mSky->Release();
	delete mSky;
}

void Game::Update(float dt)
{
	//static unsigned iteration = 0;
	Init();										// Step 1: reset forces to zero	
	//SimVel(dt);
	if (bGraviSpherees)
	{
		Solve(dt);									// Step 2: apply forces		
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


void Game::Draw()
{
	mSky->Draw();
	for(unsigned i = 0; i < numEntitys; ++i)
	{
		Entities[i]->Draw();
	}
}

void Game::SetNumEntities(unsigned numEntities_)
{
	numEntitys = numEntities_;
	//for (unsigned i = 0; i < numEntitys; ++i)
	//{
		//Entities[i] = new Entity;
	//}
	Entities = new Physics::Entity*[numEntitys];
}


void Game::AddSphere( float m, float r, const Vector3f& pos, const Vector3f& vel, const Math::Color4f& color )
{	
	
	Physics::Sphere* mass = new Physics::Sphere(m, r, pos, vel, color);
	Entities[countAddEntities] = mass;
	++countAddEntities;
}

void Game::AddPlane(float m, const Vector2f& size, const Vector3f& pos, const Vector3f& vel, const Quaternion& q, const Quaternion& qVel, const Math::Color4f& color)
{
	Physics::Plane *plane = new Physics::Plane(m, size, pos, vel, q, qVel, color);
	Entities[countAddEntities] = plane;
	++countAddEntities;
}

void Game::AddBox(float m, const Vector3f& size, const Vector3f& pos, const Vector3f& vel, const Quaternion& q, const Quaternion& qVel, const Math::Color4f& color)
{
	Physics::Box *box = new Physics::Box(m, size, pos, vel, q, qVel, color);
	Entities[countAddEntities] = box;
	++countAddEntities;
}

void Game::AddSmoker(const Vector3f& pos, const Vector3f& rand, const Vector3f& vel0, const Vector3f& vel, const Math::Color4f& color, unsigned numEntitys_, bool createCollision)
{
	Physics::Smoke *smoke = new Physics::Smoke;
	smoke->Init(1.0f, pos, rand, vel0, vel, color, numEntitys_, createCollision);
	Entities[countAddEntities] = smoke;
	++countAddEntities;
}

bool Game::AddModel(const std::string& fileName, const float m, const Vector3f& pos, const Vector3f& vel, const Math::Color4f& color)
{
	Physics::Shape* shape = new Physics::Shape(m, pos, vel, color);
	shape->Init();

	Core::FileStream fileStream;
	if (!fileStream.OpenRead(fileName))
		return false;
	

//	Core::Node node;

//	if(!fileStream.GetNode(node))
//	{
//		return false;
//	}

	//Core::Node nodeTransform;

	std::string str;

	std::cout << "Load Model Part: " << str << std::endl;

	while(!fileStream.Eof())
	{
		std::list<unsigned> CoordIndex;
		fileStream.GetParameter("coordIndex");
		CoordIndex.push_back(1);
		unsigned coordIndex;
		do
		{
			str = fileStream.GetString();
			if (str == "\"" || str == "")
				break;
			if (str == "-1")
				continue;
			coordIndex = std::stoi(str);
			CoordIndex.push_back(coordIndex);
		} while (true);


		std::list<Vector3f> Coordinate;
		fileStream.GetParameter("point");
		Coordinate.push_back(Vector3f(0.0f, 0.0f, 0.0f));
		fileStream.GetFloat();
		fileStream.GetFloat();
		Vector3f coord;
		do
		{
			str = fileStream.GetString();
			if (str == "\"" || str == "")
				break;
			float x = std::stof(str);
			float y = fileStream.GetFloat();
			float z = fileStream.GetFloat();
			coord = Vector3f(x, y, z);
			Coordinate.push_back(coord);
		} while (true);

		if (str == "")
			break;


		//shape->AddPart(Coordinate.size(), CoordIndex.size());
		shape->AddPart();


		for (std::list<Vector3f>::iterator it = Coordinate.begin(); it != Coordinate.end(); ++it)
		{
			shape->AddCoord(*it);
		}
		for (std::list<unsigned>::iterator it = CoordIndex.begin(); it != CoordIndex.end(); ++it)
		{
			shape->AddIndex(*it);
		}
	}
	
	fileStream.Close();

	Entities[countAddEntities] = shape;
	++countAddEntities;
	return true;
}

bool Game::AddVideo(const std::string& fileName, const float m, const Vector2f& size, const Vector3f& pos, const Vector3f& vel, const Quaternion& q, const Quaternion& qVel, const Math::Color4f& color)
{
	Physics::Video* video = new Physics::Video();
	video->SetMass(m);
	video->SetSize(size);
	video->SetPos(pos);
	video->SetVel(vel);
	video->SetAngleQ(q);
	video->SetAngleVelQ(qVel);
	video->SetColor(color);
	bool res = video->Initialize(fileName);
	Entities[countAddEntities] = video;
	++countAddEntities;
	return res;
}

/*
void Game::SetLine(float m, float r, float h, Vector3 pos, Quaternion q, Color4f color)
{
	Line *line = new Line;
	line->SetSphere(m);
	line->SetR(r);
	line->SetH(h);
	line->SetPos(pos);
	//line->SetPos2(pos2);
	line->SetQuaternion(q);
	line->SetColor(color);
	Entities.push_back(line);
}
*/

void Game::SimVel(float dt)
{
	for(unsigned i = 0; i < numEntitys; ++i)
	{
		Entities[i]->simulateForce(dt);
	}
}

void Game::Solve(float dt)
{
	dt;
	for(unsigned a = 0; a < numEntitys; ++a)
	{		
		for(unsigned b = 0; b < numEntitys; ++b)
		{			
			if (a != b 
				&& Math::closeEnough(Entities[a]->GetVel().x, Entities[b]->GetVel().x)
				&& Math::closeEnough(Entities[a]->GetVel().y, Entities[b]->GetVel().y)
				&& Math::closeEnough(Entities[a]->GetVel().z, Entities[b]->GetVel().z))
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

void Game::AddGraviAcc(float dt)
{
	for (unsigned i = 0; i < numEntitys; ++i)
	{
		if (typeid(*Entities[i]) == typeid(Physics::Sphere))
		{
			Entities[i]->applyAcc(graviAcc, dt);
		}
		if (typeid(*Entities[i]) == typeid(Physics::Smoke))
		{
			Entities[i]->applyAcc(graviAcc, dt);
			//Smoke* smoke = dynamic_cast<Smoke*>(Entities[i]);			
		}
	}
}

void Game::AddWindAcc(float dt)
{
	for (unsigned i = 0; i < numEntitys; ++i)
	{
		if (typeid(*Entities[i]) == typeid(Physics::Smoke))
		{
			Physics::Smoke* smoke = dynamic_cast<Physics::Smoke*>(Entities[i]);
			smoke->ApplyWind(dt);
		}
	}
}

void Game::Simulate(float dt) /* Iterate the masses by the change in time */
{
	for (unsigned i = 0; i < numEntitys; ++i)		// We will iterate every mass
	{
		Entities[i]->simulateForce(dt);				// Iterate the mass and obtain new position and new velocity
		if (typeid(*Entities[i]) == typeid(Physics::Video))
		{
			Physics::Video* video = dynamic_cast<Physics::Video*>(Entities[i]);
			video->Update(dt/TicksPerSrcond);
		}
	}
}

void Game::Collision(float dt)
{
	for (unsigned a = 0; a < numEntitys; ++a)
		for (unsigned b = a + 1; b < numEntitys; ++b)
			if (a != b)
			{
				if (typeid(*Entities[a]) == typeid(Physics::Sphere) && typeid(*Entities[b]) == typeid(Physics::Sphere))
				{
					Physics::Sphere *ma = dynamic_cast<Physics::Sphere*>(Entities[a]);
					Physics::Sphere *mb = dynamic_cast<Physics::Sphere*>(Entities[b]);
					float dist = (ma->GetPos() - mb->GetPos()).length();
					float r2 = ma->GetR() + mb->GetR();
					if (dist < r2)
					{
						float v = (ma->GetVel() - mb->GetVel()).length();
						float dc = (dist - r2) / v;
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
							float v1n = v1.dotProduct(p1p2);
							//float v1ts = v1.dotProduct(v1t);


							Vector3f p2p1 = p1 - p2;
							p2p1.unitize();
							//p1p2 = - p1p2;
							Vector3f pn2 = p2p1*v2;
							//pn2.unitize();

							Vector3f v2t = Vector3f(p2p1.x*pn2.x*pn2.x + p2p1.x*(pn2.x*pn2.y - pn2.z) + p2p1.x*(pn2.x*pn2.z + pn2.y),
								p2p1.y*(pn2.y*pn2.x + pn2.z) + p2p1.y*pn2.y*pn2.y + p2p1.y*(pn2.y*pn2.z - pn2.x),
								p2p1.z*(pn2.z*pn2.x - pn2.y) + p2p1.z*(pn2.z*pn2.y + pn2.x) + p2p1.z*pn2.z*pn2.z);

							float v2n = v2.dotProduct(p2p1);
							//float v2ts = v2.dotProduct(v2t);


							float m1 = ma->GetMass();
							float m2 = mb->GetMass();


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

							//float t1 = v11.length() + v1.length();
							//float t2 = v22.length() + v2.length();

							//ma->simulateForce(dt);
							//mb->simulateForce(dt);

							if (dist < r2)
							{
								//int t = 0;
							}
						}
					}
				}
				else if (typeid(*Entities[a]) == typeid(Physics::Sphere) && typeid(*Entities[b]) == typeid(Physics::Box) || typeid(*Entities[a]) == typeid(Physics::Box) && typeid(*Entities[b]) == typeid(Physics::Sphere))
				{
					Physics::Sphere *mass = nullptr;
					Physics::Box *box = nullptr;
					if (typeid(*Entities[a]) == typeid(Physics::Sphere) && typeid(*Entities[b]) == typeid(Physics::Box))
					{
						mass = dynamic_cast<Physics::Sphere*>(Entities[a]);
						box = dynamic_cast<Physics::Box*>(Entities[b]);						
					}
					else if (typeid(*Entities[b]) == typeid(Physics::Sphere) && typeid(*Entities[a]) == typeid(Physics::Box))
					{
						mass = dynamic_cast<Physics::Sphere*>(Entities[b]);
						box = dynamic_cast<Physics::Box*>(Entities[a]);
					}
					Vector3f pm = mass->GetPos();
					float rm = mass->GetR();
					Vector3f vm = mass->GetVel();

					Vector3f pb = box->GetPos();
					Quaternion q = box->GetAngleQ();
					Vector3f axicb;
					float angleb;
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

					Math::Plane PL[6];
					for (int i = 0; i < 6; i++)
						PL[i] = Math::Plane(P[PI[i][0]], P[PI[i][1]], P[PI[i][2]]);

					for (int i = 0; i < 6; i++)
					{
						Vector3f pr = PL[i].proj(pm);
						//float t = PL[i].a*pr.x + PL[i].b*pr.y + PL[i].c*pr.z+PL[i].d;
						//float d = PL[i].distance(pm);
						float d = (pm - pr).length();
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

								
									float sina = abs(PL[i].a*vm.x + PL[i].b*vm.y + PL[i].c*vm.z)/(sqrt(PL[i].a*PL[i].a + PL[i].b*PL[i].b + PL[i].c*PL[i].c)*vm.length());
									float angle = 90.0f - Math::radiansToDegrees(asin(sina));
									Quaternion qq;
									qq.fromAxisAngle(axic, -2.0f*angle);
									qq.normalize();
									//std::cout << "angle" << angle << std::endl;
									//std::cout << "    vm0 " << vm.x << " " << vm.y << " " << vm.z << " " << std::endl;									
									vm = qq.rotate(vm);
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
				else if (typeid(*Entities[a]) == typeid(Physics::Sphere) && typeid(*Entities[b]) == typeid(Physics::Plane) || typeid(*Entities[a]) == typeid(Physics::Plane) && typeid(*Entities[b]) == typeid(Physics::Sphere))
				{
					Physics::Sphere *mass = nullptr;
					Physics::Plane *plane = nullptr;
					if (typeid(*Entities[a]) == typeid(Physics::Sphere) && typeid(*Entities[b]) == typeid(Physics::Plane))
					{
						mass = dynamic_cast<Physics::Sphere*>(Entities[a]);
						plane = dynamic_cast<Physics::Plane*>(Entities[b]);						
					}
					else if (typeid(*Entities[b]) == typeid(Physics::Sphere) && typeid(*Entities[a]) == typeid(Physics::Plane))
					{
						mass = dynamic_cast<Physics::Sphere*>(Entities[b]);
						plane = dynamic_cast<Physics::Plane*>(Entities[a]);
					}
					Vector3f pm = mass->GetPos();
					float rm = mass->GetR();
					Vector3f vm = mass->GetVel();

					Vector3f pb = plane->GetPos();
					Quaternion q = plane->GetAngleQ();
					Vector3f axicb;
					float angleb;
					q.toAxisAngle(axicb, angleb);
					Quaternion q1;
					q1.fromAxisAngle(axicb, -angleb);
					Vector2f size = plane->GetSize();
					size *= 0.5f;

					Vector2f diff = size;

					Vector3f P[4];
					P[0] = pb + Vector3f(-diff.x, -diff.y, 0.0f);
					P[1] = pb + Vector3f(-diff.x, diff.y, 0.0f);
					P[2] = pb + Vector3f(diff.x, diff.y, 0.0f);
					P[3] = pb + Vector3f(diff.x, -diff.y, 0.0f);

					for (int i = 0; i < 4; ++i)
					{
						Vector3f d = P[i] - pb;
						d = q1.rotate(d);
						P[i] = pb + d;
					}

					Vector3f p0 = P[0];
					Vector3f p1 = P[1];
					Vector3f p2 = P[2];
					Vector3f p3 = P[3];
					Math::Plane PL = Math::Plane(p0, p1, p2);

					Vector3f pr = PL.proj(pm);
					float d = (pm - pr).length();
					
					if (d < rm)
					{
						if (InterPlanePoint(pr, p0, p1, p2, p3) || InterPlanePoint(pr, p3, p2, p1, p0))
						{
							Vector3f n(PL.a, PL.b, PL.c);
							n.unitize();
							Vector3f axic;
							axic = n*vm;
								
							if (axic.unitize() > Math::EPSILON)
							{

								
								float sina = abs(PL.a*vm.x + PL.b*vm.y + PL.c*vm.z)/(sqrt(PL.a*PL.a + PL.b*PL.b + PL.c*PL.c)*vm.length());
								float angle = 90.0f - Math::radiansToDegrees(asin(sina));
								Quaternion qq;
								qq.fromAxisAngle(axic, -2.0f*angle);
								qq.normalize();
								//std::cout << "angle" << angle << std::endl;
								//std::cout << "    vm0 " << vm.x << " " << vm.y << " " << vm.z << " " << std::endl;									
								vm = qq.rotate(vm);
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

bool Game::InterPlanePoint(Vector3f pr, Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3)
{
	Vector3f p10 = p1 - p0;
	Vector3f pm0 = pr - p0;
	float cosa = p10.dotProduct(pm0)/(p10.length()*pm0.length());
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

Vector3f Game::GraviForce( int a, int b )
{
	Vector3f f;
	float gforce;

	Vector3f Dif;
	float r;

	Vector3f t =  Entities[a]->GetPos();

	Dif = Entities[a]->GetPos() - Entities[b]->GetPos();

 	r = Dif.length();
	
	f = Entities[b]->GetPos() - Entities[a]->GetPos();
	
	gforce = float( G * double(Entities[a]->GetMass() * Entities[b]->GetMass()/(r * r))  );
	
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

void Game::SetNumStars(unsigned numStars, bool randomize /* = true */)
{
	mSky = new Physics::Sky;


	if (randomize)
	{
		mSky->Randomize();
	}
	mSky->Init(numStars);
}

bool Game::SaveData(const std::string& fileName)
{
	std::cout << "Sava Data to file: " << fileName << std::endl;
	//todo
	return true;

	/*
	std::ofstream dataFile(fileName, std::ios::out);

	if (!dataFile.is_open())
		return false;

	char space = ' ';
	float timeScale = Core::Master::Instance().GetGTimeScale();
	dataFile << timeScale << std::endl;

	unsigned UPF, FPS, UPS;
	UPF = Core::Master::Instance().GetUPF(), FPS = Core::Master::Instance().GetGFPS(), UPS = Core::Master::Instance().GetGUPS();
	dataFile << UPF << space << FPS << space << UPS << space << std::endl;
	
	
	dataFile << GetBGraviSpherees() << std::endl;

	dataFile << GetBGraviAcc() << std::endl;

	dataFile << GetBWindAcc() << std::endl;

	dataFile << GetBCollisions() << std::endl;
	
	Vector3f cameraPos = Core::Camera::Instance().GetPos();
	Vector3f cameraAxic;
	float cameraAngle;
	Core::Camera::Instance().GetQuaternion().toAxisAngle(cameraAxic, cameraAngle);
	
	dataFile << cameraPos.x << space << cameraPos.y << space << cameraPos.z << space << std::endl
		<< cameraAxic.x << space << cameraAxic.y << space << cameraAxic.z << space << cameraAngle << std::endl;
	dataFile << Core::Master::Instance().GetGUpdateCamera() << std::endl;

	Core::Master master = Core::Master::Instance();
	dataFile << master.GetLightAmient().r << space << master.GetLightAmient().g << space << master.GetLightAmient().b << space << master.GetLightAmient().a << space << std::endl;
	dataFile << master.GetLightDiffuse().r << space << master.GetLightDiffuse().g << space << master.GetLightDiffuse().b << space << master.GetLightDiffuse().a << space << std::endl;
	dataFile << master.GetLightPosition().x << space << master.GetLightPosition().y << space << master.GetLightPosition().z << space << std::endl;

	Vector3f BGraviAcc = GetGraviAcc();

	dataFile << BGraviAcc.x << space << BGraviAcc.y << space << BGraviAcc.z << space << std::endl;

	unsigned numStars = GetNumStars();
	dataFile << numStars << std::endl;
	
	unsigned numEntities = GetNumEntities();;

	dataFile << numEntities << std::endl;

	int numSphere = GetNumSpherees();	
	dataFile << numSphere << std::endl;

	int numBoxs = GetNumBoxes();
	dataFile << numBoxs << std::endl;

	dataFile << GetNumSmokers() << std::endl;
	
	float m;
	float r;
	Vector3f pos;
	Vector3f vel;		
	Math::Color4f color;

	unsigned i = 0;
	for (i; i < numSpherees; ++i)
	{
		Physics::Sphere* M = dynamic_cast<Physics::Sphere*>(Entities[i]);

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
		Physics::Box* B = dynamic_cast<Physics::Box*>(Entities[i]);

		m = B->GetMass();
		Vector3f size = B->GetSize();
		pos = B->GetPos();
		vel = B->GetVel();
		color = B->GetColor();
		Quaternion q = B->GetAngleQ();
		Vector3f angleAxic;
		float angle;
		q.toAxisAngle(angleAxic, angle);
		Quaternion qVel = B->GetAngleVelQ();
		Vector3f angleVelAxic;
		float angleVel;
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
		Physics::Smoke* S = dynamic_cast<Physics::Smoke*>(Entities[i]);

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
	*/
}

bool Game::LoadData(const std::string& fileName)
{
	std::cout << "Load " << fileName << std::endl;

	SetSceneName(fileName);

	//std::ifstream dataFile(gSceneName, std::ios::in);

	//if (!dataFile.is_open())

	Core::FileStream dataFile;
	if (!dataFile.OpenRead(fileName))
	{
		std::cerr << "Can not open file " << fileName << std::endl;
		return false;
	}

	float timeScale = dataFile.GetFloat();
	//dataFile >> timeScale;
	Core::Master::Instance().SetGTimeScale(timeScale);

	unsigned UPF = dataFile.GetUnsigned();
	unsigned FPR = dataFile.GetUnsigned();
	unsigned UPR = dataFile.GetUnsigned();
	//dataFile >> UPF>> FPR >> UPR;
	Core::Master::Instance().SetUPF(UPF);
	Core::Master::Instance().SetFPR(FPR);
	Core::Master::Instance().SetUPR(UPR);
	
	bool bGraviSpherees_ = dataFile.GetBool();
	//dataFile >> bGraviSpherees_;
	SetBGraviSpherees(bGraviSpherees_);

	bool bGraviAcc_ = dataFile.GetBool();
	//dataFile >> bGraviAcc_;
	SetBGraviAcc(bGraviAcc_);

	bool bWindAcc_ = dataFile.GetBool();
	//dataFile >> bWindAcc_;
	SetBWindAcc(bWindAcc_);

	bool bCollisions_ = dataFile.GetBool();
	//dataFile >> bCollisions_;
	SetBCollisions(bCollisions_);

	Vector3f cameraPos = dataFile.GetVector3f();
	Vector3f cameraAxic = dataFile.GetVector3f();
	float cameraAngle = dataFile.GetFloat();
	bool gUpdateCamera = dataFile.GetBool();
	//dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z		
		//>> cameraAxic.x >> cameraAxic.y >> cameraAxic.z	>> cameraAngle
		//>> gUpdateCamera;
	Core::Master::Instance().SetGUpdateCamera(gUpdateCamera);

	if (Core::Master::Instance().GetGUpdateCamera() || Core::Master::Instance().GetGFirstLoad())
	{
		Core::Master::Instance().SetGFirstLoad(false);
		Core::Camera::Instance().SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		Core::Camera::Instance().SetQuaternion(q);
	}

	Math::Color4f LightAmbient = dataFile.GetColor();
	Math::Color4f LightDiffuse = dataFile.GetColor();
	Vector3f LightPosition = dataFile.GetVector3f();
	//dataFile >> LightAmbient.r >> LightAmbient.g >> LightAmbient.b >> LightAmbient.a;
	//dataFile >> LightDiffuse.r >> LightDiffuse.g >> LightDiffuse.b >> LightDiffuse.a;
	//dataFile >> LightPosition.x >> LightPosition.y >> LightPosition.z;
	Core::Master::Instance().SetLightAmbient(LightAmbient);
	Core::Master::Instance().SetLightDiffuse(LightDiffuse);
	Core::Master::Instance().SetLightPosition(LightPosition);

	Vector3f graviAcc_ = dataFile.GetVector3f();
	//dataFile >> graviAcc_.x >> graviAcc_.y >> graviAcc_.z;
	SetGraviAcc(graviAcc_);

	unsigned numStars_ = dataFile.GetUnsigned();
	//dataFile >> numStars_;
	SetNumStars(numStars_ /*,false*/);
	
	unsigned numEntities_ = dataFile.GetUnsigned();
	//dataFile >> numEntities_;
	SetNumEntities(numEntities_);

	//unsigned numSpherees_;
	//dataFile >> numSpherees_;
	//SetNumSpherees(numSpherees_);

	//unsigned numBoxes_;
	//dataFile >> numBoxes_;
	//SetNumBoxes(numBoxes_);
	//unsigned numSmokers_;
	//dataFile >> numSmokers_;
	//SetNumSmokers(numSmokers_);

	//unsigned numShapes_;
	//dataFile >> numShapes_;
	//SetNumModels(numShapes_);

	while(countAddEntities < numEntitys)
	{
		std::string str = dataFile.GetString();
		if (str == "Sphere")
		{		
			float m = dataFile.GetFloat();
			float r = dataFile.GetFloat();
			Vector3f pos = dataFile.GetVector3f();
			Vector3f vel = dataFile.GetVector3f();
			//bool isLight = false;
			Math::Color4f color = dataFile.GetColor();
			AddSphere(m, r, pos, vel, /*isLight,*/ color);
		}
		else if (str == "Box")
		{
			float m = dataFile.GetFloat();
			Vector3f size = dataFile.GetVector3f();
			Vector3f pos = dataFile.GetVector3f();			
			Vector3f vel = dataFile.GetVector3f();			
			Vector3f angleAxic = dataFile.GetVector3f();
			float angle = dataFile.GetFloat();
			Vector3f angleVelAxic = dataFile.GetVector3f();
			float angleVel = dataFile.GetFloat();
			Math::Color4f color = dataFile.GetColor();
			//dataFile >> m
				//>> size.x >> size.y >> size.z
				//>> pos.x >> pos.y >> pos.z
				//>> vel.x >> vel.y >> vel.z
				//>> q.x >> q.y >> q.z >> angle
				//>> qVel.x >> qVel.y >> qVel.z >> angleVel
				//>> color.r >> color.g >> color.b >> color.a;
			angle = Math::degreesToRadians(angle);
			angleVel = Math::degreesToRadians(angleVel);

			Quaternion q;
			q.w = cos(angle / 2.0f);
			q.x *= sin(angle / 2.0f);
			q.y *= sin(angle / 2.0f);
			q.z *= sin(angle / 2.0f);

			Quaternion qVel;
			qVel.w = cos(angleVel / 2.0f);
			qVel.x *= sin(angleVel / 2.0f);
			qVel.y *= sin(angleVel / 2.0f);
			qVel.z *= sin(angleVel / 2.0f);

			AddBox(m, size, pos, vel, q, qVel, color);
		}
		else if (str == "Plane")
		{
			float m = dataFile.GetFloat();
			Vector2f size = dataFile.GetVector2f();
			Vector3f pos = dataFile.GetVector3f();
			Vector3f vel = dataFile.GetVector3f();
			Vector3f angleAxic = dataFile.GetVector3f();
			float angle = dataFile.GetFloat();
			Vector3f angleVelAxic = dataFile.GetVector3f();
			float angleVel = dataFile.GetFloat();
			Math::Color4f color = dataFile.GetColor();

			Quaternion q;
			q.fromAxisAngle(angleAxic, angle);
			q.normalize();

			Quaternion qVel;
			qVel.fromAxisAngle(angleVelAxic, angleVel);
			qVel.normalize();

			AddPlane(m, size, pos, vel, q, qVel, color);
		}
		else if (str == "Smoker")
		{
			unsigned numParticless = dataFile.GetUnsigned();
			bool createCollision = dataFile.GetBool();
			Vector3f pos = dataFile.GetVector3f();
			Vector3f rand = dataFile.GetVector3f();
			Vector3f vel0 = dataFile.GetVector3f();
			Vector3f vel = dataFile.GetVector3f();
			Math::Color4f color = dataFile.GetColor();			

			AddSmoker( pos, rand, vel0, vel, color, numParticless, createCollision);
		}
		else if (str == "Model")
		{
			float m = dataFile.GetFloat();			
			Vector3f pos = dataFile.GetVector3f();
			Vector3f vel = dataFile.GetVector3f();
			Math::Color4f color = dataFile.GetColor();	
			std::string fileNameModel = dataFile.GetString();

			if (!AddModel(fileNameModel, m, pos, vel, color))
			{
				std::cerr << "Can not Load Model " << fileNameModel << std::endl;
				return false;
			}
		}
		else if (str == "Video")
		{
			float m = dataFile.GetFloat();
			Vector2f size = dataFile.GetVector2f();
			Vector3f pos = dataFile.GetVector3f();
			Vector3f vel = dataFile.GetVector3f();			
			Vector3f angleAxic = dataFile.GetVector3f();
			float angle = dataFile.GetFloat();
			Vector3f angleVelAxic = dataFile.GetVector3f();
			float angleVel = dataFile.GetFloat();
			Math::Color4f color = dataFile.GetColor();
			std::string fileNameVideo = dataFile.GetString();

			Quaternion q;
			q.fromAxisAngle(angleAxic, angle);
			q.normalize();

			Quaternion qVel;
			qVel.fromAxisAngle(angleVelAxic, angleVel);
			qVel.normalize();

			if (!AddVideo(fileNameVideo, m, size, pos, vel, q, qVel, color))
			{
				std::cerr << "Can not Load Video " << fileNameVideo << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "Can not open file " << fileName << std::endl;
			return false;
		}
	}

	dataFile.Close();
	return true;
}