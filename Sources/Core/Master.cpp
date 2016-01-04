#include "Master.h"

#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

#include "RenderGL.h"
#include "Input.h"

#include "../Constans.h"
#include "../GameBase.h"
//#include "../Camera.h"
#include "../Math/Color.h"

using namespace Core;

bool gKeys[256];					// Массив, используемый для операций с клавиатурой
bool gLightOnKey = false;			// L нажата?
bool gShowDebugInfoKey = false;		// TAB нажат?
bool gReverseKeyPress = false;		// Q нажат?
bool gUpdateKeyPress = false;

unsigned gSceneNum = 0;
unsigned gSceneNumMax = 9;

float gTimeScale = 1.0f;
float gAngleScale = 1.0f;
float gMoveScale = 1.0f;
float gShiftScale = 0.1f;

bool  done = false;	// Логическая переменная для выхода из цикла

bool gActive = true;                // Флаг активности окна
bool gPause = true;
bool gShowDebugInfo = true;
//bool gUpdateCamera = false;
//bool gFirstLoad = false;


float gfps = 0.0f;
float gTime = 0.0f;


Color4f gLightAmbient( 0.8f, 0.8f, 0.8f, 1.0f );//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
Color4f gLightDiffuse( 1.0f, 1.0f, 1.0f, 1.0f );//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
Vector3 gLightPosition( 3.0f, 3.0f, 4.0f );//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света


float framesPerSecond = 0.0f;
float lastTime = 0.0f;

long tickCount = 0;
long lastTickCount = 0;

GameBase *gmGame;

Render* gmRender = new RenderGL;

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
			gmRender->ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// Младшее слово=Width, старшее слово=Height
			return 0;											// Возвращаемся
		}
	}
	// пересылаем все необработанные сообщения DefWindowProc
	return DefWindowProc( (HWND) hWnd, uMsg, wParam, lParam );
}

void Master::Init(GameBase* gameBase_)
{
	gmGame = gameBase_;

	//Camera::Init();
	//if (!LoadData(gSceneNum)) 
	//{
		//std::cerr << "Load Data Failed!" << std::endl;
		//return;													// Return False (Failure)
	//}
	// Создать наше OpenGL окно	
	if (!gmRender->CreateWin( (long*)WndProc, "Gravi Engine", gcWidth, gcHeight, 32))
	{
		std::cerr << "CreateWin Failed!" << std::endl;
		return;              // Выйти, если окно не может быть создано
	}
}

void Master::Run()
{
	lastTickCount = ::GetTickCount();		// Get Tick Count

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

			Input::Instance().UpdateKeys();
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

		gmGame->Update(gTimeScale*dt);
	}

	framesPerSecond = framesPerSecond + 1.0f;
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
	gmRender->BeginDraw();	
	gmGame->Draw();
	if (gShowDebugInfo)
	{
		gmRender->DrawDebugInfo();
	}
	gmRender->EndDraw();
}

bool Master::LoadData(unsigned fileNum)
{
	gSceneNum = fileNum;

	std::string fileNumstr = std::to_string(fileNum);
	std::string fileName = "data//data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);

	if (!dataFile.is_open())
		return false;
	dataFile.close();
	return true;
}

void Master::Release()
{
	gmGame->Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
	gmRender->Release();						// Разрушаем окно
}

bool Master::SaveData(const std::string& fileName)
{
	std::string fileNamestr = "../data/" + fileName;
	std::ofstream dataFile(fileName, std::ios::out);
	if (!dataFile.is_open())
		return false;

	dataFile << "Be Happy" << std::endl;
	dataFile.close();

	return true;
}