#include "Master.h"

#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

#include "RenderGL.h"
#include "Camera.h"

#include "../Constans.h"
#include "../Math/Color.h"

using namespace Core;

unsigned gcWidth = 1920;
unsigned gcHeight = 1080;

bool gFirstLoad = true;

bool gLightOnKey = false;			// L нажата?
bool gShowDebugInfoKey = false;		// TAB нажат?
bool gReverseKeyPress = false;		// Q нажат?
bool gReloadKeyPress = false;
bool gSaveKeyPress = false;

Color4f gLightAmbient( 0.8f, 0.8f, 0.8f, 1.0f );//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
Color4f gLightDiffuse( 1.0f, 1.0f, 1.0f, 1.0f );//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
Vector3 gLightPosition( 3.0f, 3.0f, 4.0f );//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света


unsigned countUpdate = 0;
unsigned countDraw = 0;
unsigned count = 0;

long tickCount = 0;
long lastTickCount = 0;
long lastTickFPS = 0;
long lastTickUPS = 0;

float64 minFPS = 100.0;
float64 minUPS = 200.0;

GameBase *gmGame;

bool irstLoad = false;



bool Master::gKeys[256];

float64 Master::gfps = 0.0;
float64 Master::gups = 0.0;

float64 Master::gTime = 0.0;

//unsigned Master::gSceneNum = 1;
unsigned Master::gSceneNumMax = 9;

float64 Master::gTimeScale = 1.0f;

float64 Master::gAngleScale = 0.001f;
float64 Master::gMoveScale = 0.1f;
float64 Master::gShiftScale = 0.1f;

bool Master::gDone = false;	// Логическая переменная для выхода из цикла

bool Master::gActive = true;                // Флаг активности окна
bool Master::gPause = true;
bool Master::gShowDebugInfo = true;
//bool gUpdateCamera = false;
//bool gFirstLoad = false;


Master::Master()
{
}

Master::~Master()
{

}


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

void Master::Init(GameBase* gameBase_)
{
	gmGame = gameBase_;

	// Создать наше OpenGL окно	
	bool assert = !RenderGL::Instance().CreateWin( (long*)WndProc, "Gravi Engine", gcWidth, gcHeight, 32);
	if (assert)
	{
		std::cerr << "CreateWin Failed!" << std::endl;
		return;              // Выйти, если окно не может быть создано
	}
}

void Master::Run()
{
	lastTickCount = ::GetTickCount();		// Get Tick Count
	lastTickFPS = lastTickCount;
	lastTickUPS = lastTickCount;

	MSG  msg;           // Структура для хранения сообщения Windows

	while( !gDone )							// Цикл продолжается, пока done не равно true
	{
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )    // Есть ли в очереди какое-нибудь сообщение?
		{
			if( msg.message == WM_QUIT )						// Мы поучили сообщение о выходе?
			{
				gDone = true;										// Если так, done=true
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
				tickCount = GetTickCount();			// Get The Tick Count
				//float64 currentTime = float64(tickCount) * 0.001;

				count += tickCount - lastTickCount;

				if (count > 1000)
				{
					count -= 1000;
					gups = float64(countUpdate);
					gfps = float64(countDraw);
					countUpdate = 0;
					countDraw  = 0;
				}

				//if (!gPause && (tickCount - lastTickUPS) > long(1000.0/minUPS))
				if (!gPause)
				{
					Update();
					lastTickUPS = tickCount;
					countUpdate++;					
				}
				

				if ( float64(tickCount - lastTickFPS) > long(1000.0/minFPS))
				{
					Draw();							// Рисуем сцену
					lastTickFPS = tickCount;
					countDraw++;
				}				
				lastTickCount = tickCount;			// Set Last Count To Current Count
			}

			UpdateKeys();
		}
	}
}

void Master::Update()
{
	float64 dt = float64(tickCount - lastTickCount) * 0.001;
	gTime += gTimeScale*dt;
	gmGame->Update(gTimeScale*dt);
}


void Master::Draw()                // Здесь будет происходить вся прорисовка
{
	RenderGL::Instance().BeginDraw();	
	gmGame->Draw();
	if (gShowDebugInfo)
	{
		RenderGL::Instance().DrawDebugInfo();
	}
	RenderGL::Instance().EndDraw();
}

void Master::Release()
{
	gmGame->Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
	//RenderGL::Instance().Release();						// Разрушаем окно
}

bool Master::LoadData(unsigned fileNum)
{
	return gmGame->LoadData(fileNum);

	//GameBase::Instance().SetSceneNum(fileNum);

	//std::string fileNumstr = std::to_string(fileNum);
	//std::string fileName = "data//data" + fileNumstr + ".dat";
	//std::ifstream dataFile(fileName, std::ios::in);

	//if (!dataFile.is_open())
	//return false;
	//dataFile.close();
	//return true;
}

bool Master::SaveData(const std::string& fileName)
{
	std::string fileNamestr = "data/" + fileName;
	std::ofstream dataFile(fileNamestr, std::ios::out);
	if (!dataFile.is_open())
		return false;

	dataFile << "Be Happy" << std::endl;
	dataFile.close();

	return true;
}

void Master::UpdateKeys()
{
	
	if( gKeys[VK_F1] )				// Была ли нажата F1?
	{
		gKeys[VK_F1] = false;			// Если так, меняем значение ячейки массива на false
		RenderGL::Instance().Release();					// Разрушаем текущее окно
		RenderGL::Instance().SetFullScreen( !RenderGL::Instance().GetFullScreen() );		// Переключаем режим
		// Пересоздаём наше OpenGL окно
		gDone = !RenderGL::Instance().CreateWin((long*)Master::Instance().WndProc, ("NeHe OpenGL структура"), gcWidth, gcHeight, 32 );
	}

	if( !gReloadKeyPress && gKeys[VK_F5])
	{
		gKeys[VK_F5] = false;
		gReloadKeyPress = false;

		Master::Instance().Release();		
		gDone = !Master::Instance().LoadData(gmGame->GetSceneNum());
		RenderGL::Instance().SetGLLight();
	}

//	if ( gReloadKeyPress && gKeys[VK_F5] )
//	{
//		gKeys[VK_F5] = false;
//		gReloadKeyPress = false;		
//	}


	if ( !gSaveKeyPress && gKeys[VK_F6])
	{
		gKeys[VK_F6] = false;
		gSaveKeyPress = true;
		
		gDone = !Master::Instance().SaveData("quickSave");
	}

//	if ( gSaveKeyPress && gKeys[VK_F6] )
//	{
//		gKeys[VK_F6] = false;
//		gSaveKeyPress = false;
//	}



	if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
	{
		gDone = true;							// ESC говорит об останове выполнения программы
	}
	
	if ( gKeys[VK_SPACE] )
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}

	if ( gShowDebugInfoKey && gKeys[VK_TAB] )
	{
		gKeys[VK_TAB] = false;
		gShowDebugInfoKey = false;
		gShowDebugInfo = !gShowDebugInfo;		
	}

	if ( !gShowDebugInfoKey && gKeys[VK_TAB] )
	{
		gShowDebugInfoKey = true;
	}


	if ( gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.1f*gTimeScale;
	}

	if ( !gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.001f;
	}

	if ( !gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.001f;
	}

	if ( gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.1f*gTimeScale;
	}	
	
	if( gKeys[VK_RIGHT] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateLR(gAngleScale);
		else
			Camera::Instance().RotateLR(gShiftScale*gAngleScale);				
	}

	if( gKeys[VK_LEFT] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateLR(-gAngleScale);			
		else
			Camera::Instance().RotateLR(-gShiftScale*gAngleScale);			
	}

	if( gKeys[VK_UP] )
	{								
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateUpDown(gAngleScale);
		else
			Camera::Instance().RotateUpDown(gShiftScale*gAngleScale);
	}

	if( gKeys[VK_DOWN] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateUpDown(-gAngleScale);
		else
			Camera::Instance().RotateUpDown(-gShiftScale*gAngleScale);
	}

	if ( gKeys[VK_SHIFT] && gKeys['0'] )
	{
		gTimeScale = -1.0f;
	}
	else if ( gKeys['0'] )
	{
		gTimeScale = 0.0f;
	}

	
	if( gKeys['W'] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveCamera(-gMoveScale);
		else
			Camera::Instance().MoveCamera(-gShiftScale*gMoveScale);
	}

	if( gKeys['S'] ) 
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveCamera(gMoveScale);
		else
			Camera::Instance().MoveCamera(gShiftScale*gMoveScale);
	}

	if( gKeys['A'] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveLRCamera(gMoveScale);
		else
			Camera::Instance().MoveLRCamera(gShiftScale*gMoveScale);
	}

	if( gKeys['D'] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveLRCamera(-gMoveScale);
		else
			Camera::Instance().MoveLRCamera(-gShiftScale*gMoveScale);
	}
	

	if ( gKeys['L'] && !gLightOnKey )			// Клавиша 'L' нажата и не удерживается?
	{
		gLightOnKey=true;						// lp присвоили TRUE
		RenderGL::Instance().SetLightOn(!RenderGL::Instance().GetLightOn());				// Переключение света TRUE/FALSE
		if (RenderGL::Instance().GetLightOn())					// Если не свет
		{
			RenderGL::Instance().EnableLight();
		}
		else							// В противном случае
		{
			RenderGL::Instance().DisableLight();
		}
	}

	if ( !gKeys['L'] )					// Клавиша 'L' Отжата?
	{
		gLightOnKey=false;						// Если так, то lp равно FALSE
	}

	if( gKeys['R'] )
	{
		gTimeScale = 1.0f;
	}

	if( gKeys['Q'] && !gReverseKeyPress )
	{
		gTimeScale = -gTimeScale;
		gReverseKeyPress = true;
	}

	if ( !gKeys['Q'] && gReverseKeyPress )
	{
		gReverseKeyPress = false;
	}
	
	for (unsigned char i = 0; i < gSceneNumMax; i++)
	{
		unsigned char c = '1' + i;
		if ( gKeys[c] )
		{
			gKeys[c] = false;
			gFirstLoad = true;
			Master::Instance().Release();
			gDone = !Master::Instance().LoadData(i + 1);
			RenderGL::Instance().SetGLLight();
		}
	}
}