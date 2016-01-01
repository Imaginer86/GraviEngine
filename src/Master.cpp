#include "Master.h"
#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

#include "RenderGL.h"
#include "Platform.h"
#include "Input.h"
#include "Game.h"

#include "Camera.h"
#include "Sky.h"

extern bool gActive;
extern float gfps;
extern bool gKeys[256];
extern bool gPause;
extern float gTime;
extern bool gShowDebugInfo;
extern float gTimeScale;
extern bool gFirstLoad;
extern unsigned gSceneNum;
extern bool gUpdateCamera;

//extern Camera mCamera;
//extern Sky mSky;

extern float gLightAmbient[4];//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
extern float gLightDiffuse[4];//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
extern float gLightPosition[4];//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света


float framesPerSecond = 0.0f;
float lastTime = 0.0f;

long tickCount = 0;
long lastTickCount = 0;


long Master::WndProc(  void*  hWnd,				// Дескриптор нужного окна
			 unsigned int	uMsg,				// Сообщение для этого окна
			 unsigned int	wParam,            // Дополнительная информация
			 unsigned int	lParam)            // Дополнительная информация
{
	switch (uMsg)                // Проверка сообщения для окна
	{
	case WM_ACTIVATE:            // Проверка сообщения активности окна
		{
			if( !HIWORD( wParam ) )          // Проверить состояние минимизации
			{
				gActive = true;					// Программа активна
			}
			else
			{
				gActive = false;					// Программа теперь не активна
			}

			return 0;						// Возвращаемся в цикл обработки сообщений
		}
	case WM_SYSCOMMAND:            // Перехватываем системную команду
		{
			switch ( wParam )            // Останавливаем системный вызов
			{
			case SC_SCREENSAVE:				// Пытается ли запустится скринсейвер?
			case SC_MONITORPOWER:			// Пытается ли монитор перейти в режим сбережения энергии?
				return 0;						// Предотвращаем это
			}
			break;              // Выход
		}
	case WM_CLOSE:              // Мы получили сообщение о закрытие?
		{
			PostQuitMessage( 0 );			// Отправить сообщение о выходе
			return 0;							// Вернуться назад
		}

	case WM_KEYDOWN:            // Была ли нажата кнопка?
		{
			gKeys[wParam] = true;			// Если так, мы присваиваем этой ячейке true
			return 0;							// Возвращаемся
		}
	case WM_KEYUP:              // Была ли отпущена клавиша?
		{
			gKeys[wParam] = false;			//  Если так, мы присваиваем этой ячейке false
			return 0;						// Возвращаемся
		}
	case WM_SIZE:              // Изменены размеры OpenGL окна
		{
			RenderGL::Instance().ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// Младшее слово=Width, старшее слово=Height
			return 0;											// Возвращаемся
		}
	}
	// пересылаем все необработанные сообщения DefWindowProc
	return DefWindowProc( (HWND) hWnd, uMsg, wParam, lParam );
}

void Master::Run()
{

	bool  done = false;	// Логическая переменная для выхода из цикла


	lastTickCount = Platform::Instance().GetTickCount();		// Get Tick Count


	MSG  msg;           // Структура для хранения сообщения Windows

	while( !done )							// Цикл продолжается, пока done не равно true
	{
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )    // Есть ли в очереди какое-нибудь сообщение?
		{
			if( msg.message == WM_QUIT )						// Мы поучили сообщение о выходе?
			{
				done = true;										// Если так, done=true
			}
			else												// Если нет, обрабатывает сообщения
			{
				TranslateMessage( &msg );							// Переводим сообщение
				DispatchMessage( &msg );							// Отсылаем сообщение
			}
		}
		else	// Если нет сообщений
		{
			// Прорисовываем сцену.
			if( gActive )          // Активна ли программа?
			{
				Update();
				Draw();						// Рисуем сцену
			}

			if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
			{
				done = true;							// ESC говорит об останове выполнения программы
			}

			if (!Input::Instance().UpdateKeys())
			{
				done = true;

				std::cerr << "Uodate Keys Failed!" << std::endl;			
				//MessageBox(NULL, "Uodate Keys Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			
			}
		}
	}
}

void Master::Update()
{
	tickCount = GetTickCount();				// Get The Tick Count

	if (!gPause)
	{			
		float dt = float(tickCount - lastTickCount) * 0.001f;
		gTime += gTimeScale*dt;

		Game::Instance().Update(gTimeScale*dt);
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

}


void Master::Draw()                // Здесь будет происходить вся прорисовка
{
	RenderGL::Instance().BeginDraw();	
	Game::Instance().Draw();
	if (gShowDebugInfo)
	{
		RenderGL::Instance().DrawDebugInfo();
	}
	RenderGL::Instance().EndDraw();
}

bool Master::LoadData(unsigned fileNum)
{
	gSceneNum = fileNum;

	std::string fileNumstr = std::to_string(fileNum);

	//!!!char* fileNameCharPtr = "0";
	//!!!std::string fileNumstr = itoa(fileNum, fileNameCharPtr,1);

	std::string fileName = "..//data//data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);

	//!!!std::ifstream dataFile(fileNameCharPtr, std::ios::in);

	if (!dataFile)
		return false;


	bool bGraviMasses;
	dataFile >> bGraviMasses;
	Game::Instance().SetBGraviMasses(bGraviMasses);

	bool bGraviAcc;
	dataFile >> bGraviAcc;
	Game::Instance().SetBGraviAcc(bGraviAcc);

	bool bWindAcc;
	dataFile >> bWindAcc;
	Game::Instance().SetBWindAcc(bWindAcc);

	bool bCollisions;
	dataFile >> bCollisions;
	Game::Instance().SetBCollisions(bCollisions);

	unsigned long numStars;
	dataFile >> numStars;
	if (numStars)
	{
		Game::Instance().SetNumStars(numStars /*,false*/);
	}

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
		Camera::Instance().SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		Camera::Instance().SetQuaternion(q);
	}

	dataFile >> gLightAmbient[0] >> gLightAmbient[1] >> gLightAmbient[2] >> gLightAmbient[3];
	dataFile >> gLightDiffuse[0] >> gLightDiffuse[1] >> gLightDiffuse[2] >> gLightDiffuse[3];
	dataFile >> gLightPosition[0] >> gLightPosition[1] >> gLightPosition[2] >> gLightPosition[3];

	RenderGL::Instance().rLightAmbient = gLightAmbient;
	RenderGL::Instance().rLightDiffuse = gLightDiffuse;
	RenderGL::Instance().rLightPosition = gLightPosition;


	Vector3 graviAcc;

	dataFile >> graviAcc.x >> graviAcc.y >> graviAcc.z;
	Game::Instance().SetGraviAcc(graviAcc);

	unsigned int numEntities = 0;

	dataFile >> numEntities;

	Game::Instance().SetNumEntities(numEntities);

	int numMass = 0;

	dataFile >> numMass;

	for (int i = 0; i < numMass; i++)
	{
		float m = 0.0f, r = 0.0f;
		Vector3 pos, vel;
		//bool isLight = false;
		Color4f color(0.0f, 0.0f, 0.0f, 0.0f);
		dataFile >> m >> r
			>> pos.x >> pos.y >> pos.z
			>> vel.x >> vel.y >> vel.z
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		Game::Instance().AddMass(m, r, pos, vel, /*isLight,*/ color);
	}

	int numBoxs = 0;
	dataFile >> numBoxs;

	for (int i = 0; i < numBoxs; i++)
	{
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

		Game::Instance().AddBox(m, size, pos, vel, q, qVel, color);
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

		Game::Instance().AddSmoker( pos, rand, vel0, vel, color, numParticless);
	}
		

	/*	int numLines = 0;
	//dataFile >> numLines;
	//Game::Instance().SetNumLines(numLines);
	for(int i = 0; i < numLines; i++)
	{
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
	Game::Instance().SetLine(m, r, h, pos, q, color);
	}
	*/

	dataFile.close();
	return true;
}

void Master::Release()
{
	Game::Instance().Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
}

bool Master::SaveData(const std::string& fileName)
{
	return true;
}