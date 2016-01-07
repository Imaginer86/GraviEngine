#include "GameBase.h"
#include <string>
#include <fstream>

GameBase::GameBase()
{

}

GameBase::~GameBase()
{

}

void GameBase::Release() /* delete the masses created */
{

}


void GameBase::Init() /* this method will call the init() method of every mass */
{
	//Ahtung
	//Camera::Instance().Init();
}

void GameBase::Update(float64 dt)
{
	dt;
}

void GameBase::Draw()
{

}


bool GameBase::LoadData(unsigned fileNum)
{
	
	gSceneNum = fileNum;

	std::string fileNumstr = std::to_string(fileNum);
	std::string fileName = "data//data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);

	if (!dataFile.is_open())
		return false;

	/*

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
		SetNumStars(numStars);
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
		//gcCamera.SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		//Camera::Instance().SetQuaternion(q);
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
		AddMass(m, r, pos, vel, / color);
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
		q.w = cosf(angle / 2.0f);
		q.x *= sinf(angle / 2.0f);
		q.y *= sinf(angle / 2.0f);
		q.z *= sinf(angle / 2.0f);

		qVel.w = cosf(angleVel / 2.0f);
		qVel.x *= sinf(angleVel / 2.0f);
		qVel.y *= sinf(angleVel / 2.0f);
		qVel.z *= sinf(angleVel / 2.0f);

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

	*/

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