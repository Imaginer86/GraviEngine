//#pragma once
//#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>

					   

#include "Game.h"
#include "Camera.h"
#include "Color.h"

#include "Math\Math.h"

#include "RenderGL.h"
#include "Input.h"
#include "Platform.h"


//Error
typedef long (long)(HWND,UINT,WPARAM,LPARAM);


//HWND	hWnd = nullptr;              // Здесь будет хранится дескриптор окна
#define VK_ESCAPE         0x1B

const int gWidth = 1600;
const int gHeight = 900;

bool gLightOnKey = false;			// L нажата?
bool gShowDebugInfo = true;
bool gShowDebugInfoKey = false;		// TAB нажат?
//bool gShowResetKey = false;			// R нажат?
bool gReverseKeyPress = false;		// Q нажат?

bool gKeys[256];					// Массив, используемый для операций с клавиатурой

bool gActive = true;                // Флаг активности окна, установленный в true по умолчанию

bool gPause = true;

float gTimeScale = 1.0f;
float gTime = 0.0f;

float gAngleScale = 1.0f;
float gMoveScale = 1.0f;
float gShiftScale = 0.1f;

float gfps = 0.0f;
float gups = 0.0f;

unsigned gSceneNum = 2;
unsigned gSceneNumMax = 8;

float gLightAmbient[4];//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
float gLightDiffuse[4];//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
float gLightPosition[4];//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

bool gUpdateCamera = false;
bool gFirstLoad = true;


Game mGame;
Camera mCamera;
Render* mRender = new RenderGL;
Input* mInput = new Input;
//Platform mPlatform;


void Draw()                // Здесь будет происходить вся прорисовка
{
	mRender->BeginDraw();
	mGame.Draw();
	if (gShowDebugInfo)
		mRender->DrawDebugInfo();
	mRender->EndDraw();
}

void Release()
{
	mGame.Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
}

bool LoadData(unsigned fileNum)
{
	gSceneNum = fileNum;

	std::string fileNumstr = std::to_string(fileNum);
	std::string fileName = "data//data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);
	if (!dataFile)
		return false;

	Vector3 cameraPos;
	Vector3 cameraAxic;
	float cameraAngle;

	dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z
		>> cameraAxic.x >> cameraAxic.y >> cameraAxic.z
		>> cameraAngle;
	dataFile >> gUpdateCamera;

	if (gUpdateCamera || gFirstLoad)
	{
		gFirstLoad = false;
		mCamera.SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		mCamera.SetQuaternion(q);
	}

	dataFile >> gLightAmbient[0] >> gLightAmbient[1] >> gLightAmbient[2] >> gLightAmbient[3];
	dataFile >> gLightDiffuse[0] >> gLightDiffuse[1] >> gLightDiffuse[2] >> gLightDiffuse[3];
	dataFile >> gLightPosition[0] >> gLightPosition[1] >> gLightPosition[2] >> gLightPosition[3];

	mRender->rLightAmbient = gLightAmbient;
	mRender->rLightDiffuse = gLightDiffuse;
	mRender->rLightPosition = gLightPosition;


	Vector3 graviAcc;

	dataFile >> graviAcc.x >> graviAcc.y >> graviAcc.z;
	mGame.SetGraviAcc(graviAcc);

	unsigned int numEntities = 0;

	dataFile >> numEntities;

	mGame.SetNumEntities(numEntities);

	int numMass = 0;

	dataFile >> numMass;

	//mGame.SetNumMasses(numMass);

	for (int i = 0; i < numMass; i++) {
		float m = 0.0f, r = 0.0f;
		Vector3 pos, vel;
		//bool isLight = false;
		Color4f color(0.0f, 0.0f, 0.0f, 0.0f);
		dataFile >> m >> r
			>> pos.x >> pos.y >> pos.z
			>> vel.x >> vel.y >> vel.z
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetMass(m, r, pos, vel, /*isLight,*/ color);
	}

	int numBoxs = 0;
	dataFile >> numBoxs;

	//mGame.SetNumBoxes(numBoxs);
	for (int i = 0; i < numBoxs; i++) {
		float m = 0.0;
		Vector3 pos, size, vel;
		Color4f color;
		Quaternion q;
		Quaternion qVel;
		float angle, angleVel;
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

		mGame.SetBox(m, size, pos, vel, q, qVel, color);
	}

	/*	int numLines = 0;
	//dataFile >> numLines;
	//mGame.SetNumLines(numLines);
	for(int i = 0; i < numLines; i++) {
	float m = 0.0f, r = 0.0f, h = 0.0f;
	Vector3 pos;
	Color4f color;
	Quaternion q;
	Vector3 u;
	float w = 0.0f;
	dataFile >> m >> r >> h
	>> pos.x >> pos.y >> pos.z
	>> u.x >> u.y >> u.z >> w
	>> color.r >> color.g >> color.b >> color.a;
	q.fromAxisAngle(u, w);
	mGame.SetLine(m, r, h, pos, q, color);
	}
	*/

	dataFile.close();
	return true;
}


//LRESULT  CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );        // Прототип функции WndProc
//long WndProc(  HWND  hWnd,				// Дескриптор нужного окна
						 //UINT  uMsg,				// Сообщение для этого окна
						 //WPARAM  wParam,            // Дополнительная информация
						 //LPARAM  lParam);            // Дополнительная информация



bool UpdateKeys()
{
	return mInput->UpdateKeys();
}


//int WINAPI WinMain(	HINSTANCE  hInstance,				// Дескриптор приложения
//					HINSTANCE  hPrevInstance,			// Дескриптор родительского приложения
//					LPSTR    lpCmdLine,					// Параметры командной строки
//					int    nCmdShow */)					// Состояние отображения окна


int main()
{
	int t = float(0);


	std::cout << "Hello" << std::endl;
	std::cerr << "And Your Hello" << std::endl;

	//mRender->rhInstance = hInstance;
	//mRender.rhWnd = hWnd;
	mRender->rCamera = &mCamera;
	mRender->rSceneNum = &gSceneNum;
	mRender->rfps = &gfps;
	mRender->rups = &gups;
	mRender->rTimeScale = &gTimeScale;
	mRender->rTime = &gTime;

	if (!LoadData(gSceneNum)) 
	{
		//MessageBox (NULL, "Load Data Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		std::cerr << "Load Data Failed!" << std::endl;

		return 1;													// Return False (Failure)
	}

	// Создать наше OpenGL окно
	if (!mRender->CreateWin(&Platform::Instance().WndProc, "Gravi Engine", gWidth, gHeight, 32))
	{
		//MessageBox (NULL, "CreateWin Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		std::cerr << "CreateWin Failed!" << std::endl;
		return 1;              // Выйти, если окно не может быть создано
	}

	// Спрашивает пользователя, какой режим экрана он предпочитает
	//if( MessageBox( NULL, "Хотите ли Вы запустить приложение в полноэкранном режиме?",  "Запустить в полноэкранном режиме?", MB_YESNO | MB_ICONQUESTION) == IDNO )
	//{		
		//fullscreen = false;          // Оконный режим
	//

	//std::cout  << "Хотите ли Вы запустить приложение в полноэкранном режиме? Y/N? " << std::endl;
	


	bool  done = false;	// Логическая переменная для выхода из цикла

	unsigned long tickCount = 0;
	unsigned long lastTickCount = 0;

	lastTickCount = mPlatform.GetTickCount();		// Get Tick Count

	float framesPerSecond = 0.0f;
	float lastTime = 0.0f;

	MSG  msg;           // Структура для хранения сообщения Windows

	while( !done )							// Цикл продолжается, пока done не равно true
	{
		if( mPlatform.PeekMessage( msg ) )    // Есть ли в очереди какое-нибудь сообщение?
		{
			if( msg.message == WM_QUIT )						// Мы поучили сообщение о выходе?
			{
				done = true;										// Если так, done=true
			}
			else												// Если нет, обрабатывает сообщения
			{
				mPlatform.TranslateMessage( msg );							// Переводим сообщение
				mPlatform.DispatchMessage( msg );							// Отсылаем сообщение
			}
		}
		else	// Если нет сообщений
		{
				// Прорисовываем сцену.
			if( gActive )          // Активна ли программа?
			{
				tickCount = GetTickCount();				// Get The Tick Count
				
				if (!gPause)
				{			
					float dt = float(tickCount - lastTickCount) * 0.001f;
					gTime += gTimeScale*dt;

					mGame.Update(gTimeScale*dt);
				} 					
				framesPerSecond++;
				float currentTime = float(tickCount)*0.001f;
				if ((currentTime - lastTime) > 1.0f)
				{
					lastTime = currentTime;
					gfps = framesPerSecond;
					framesPerSecond = 0.0f;
				}
				lastTickCount = tickCount;			// Set Last Count To Current Count

				Draw();						// Рисуем сцену
						
			}

			if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
			{
				done = true;							// ESC говорит об останове выполнения программы
			}

			if (!UpdateKeys())
			{
				done = true;
				//MessageBox(NULL, "Uodate Keys Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
				std::cerr << "Uodate Keys Failed!" << std::endl;
			}
		}
	}

	// Shutdown
	mRender->Release();						// Разрушаем окно
	
	return ( int(msg.wParam) );              // Выходим из программы
}

