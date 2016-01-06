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

bool Master::gKeys[256];

bool Master::gLightOnKey = false;			// L нажата?
bool Master::gShowDebugInfoKey = false;		// TAB нажат?
bool Master::gReverseKeyPress = false;		// Q нажат?
bool Master::gUpdateKeyPress = false;

//unsigned Master::gSceneNum = 1;
unsigned Master::gSceneNumMax = 9;

float64 Master::gTimeScale = 1.0f;
float64 Master::gAngleScale = 1.0f;
float64 Master::gMoveScale = 1.0f;
float64 Master::gShiftScale = 0.1f;

bool Master::gDone = false;	// Логическая переменная для выхода из цикла

bool Master::gActive = true;                // Флаг активности окна
bool Master::gPause = true;
bool Master::gShowDebugInfo = true;
//bool gUpdateCamera = false;
//bool gFirstLoad = false;


float64 Master::gfps = 0.0f;
float64 Master::gTime = 0.0f;




Color4f gLightAmbient( 0.8f, 0.8f, 0.8f, 1.0f );//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
Color4f gLightDiffuse( 1.0f, 1.0f, 1.0f, 1.0f );//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
Vector3 gLightPosition( 3.0f, 3.0f, 4.0f );//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света


float64 framesPerSecond = 0.0f;
float64 lastTime = 0.0f;

long tickCount = 0;
long lastTickCount = 0;

GameBase *gmGame;

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



	//Camera::Instance().Init();
	
	//if (!LoadData(gSceneNum)) 
	//{
		//std::cerr << "Load Data Failed!" << std::endl;
		//return;													// Return False (Failure)
	//}

	// Создать наше OpenGL окно	
	if (!RenderGL::Instance().CreateWin( (long*)WndProc, "Gravi Engine", gcWidth, gcHeight, 32))
	{
		std::cerr << "CreateWin Failed!" << std::endl;
		return;              // Выйти, если окно не может быть создано
	}
}

void Master::Run()
{
	lastTickCount = ::GetTickCount();		// Get Tick Count

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
				Update();
				Draw();						// Рисуем сцену
			}

			UpdateKeys();
		}
	}
}

void Master::Update()
{
	tickCount = GetTickCount();				// Get The Tick Count

	if (!gPause)
	{			
		float64 dt = float64(tickCount - lastTickCount) * 0.001;
		gTime += gTimeScale*dt;
		gmGame->Update(gTimeScale*dt);
	}

	lastTickCount = tickCount;			// Set Last Count To Current Count
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

	framesPerSecond = framesPerSecond + 1.0;
	float64 currentTime = float64(tickCount) * 0.001;

	if ((currentTime - lastTime) > 1.0)
	{
		lastTime = currentTime;
		gfps = framesPerSecond;
		framesPerSecond = 0.0f;
	}
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

void Master::Release()
{
	gmGame->Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
	//RenderGL::Instance().Release();						// Разрушаем окно
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

	if( gUpdateKeyPress && gKeys[VK_F5] == true )
	{
		gKeys[VK_F5] = false;
		gUpdateKeyPress = true;
		Master::Instance().Release();		
		gDone = !Master::Instance().LoadData(gmGame->GetSceneNum());
		RenderGL::Instance().SetGLLight();
	}

	if ( gUpdateKeyPress && gKeys[VK_F6] == true )
	{
		gKeys[VK_F6] = false;
		gUpdateKeyPress = false;
		Master::Instance().Release();
		gDone = !Master::Instance().SaveData("dataSave");
	}

	if ( !gUpdateKeyPress && gKeys[VK_F6] == false )
	{
		gUpdateKeyPress = true;
	}

	if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
	{
		gDone = true;							// ESC говорит об останове выполнения программы
	}
	
	if ( gKeys[VK_SPACE] )
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
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
	

	if ( gKeys[VK_TAB] && !gShowDebugInfoKey )
	{
		gShowDebugInfoKey = true;
		gShowDebugInfo = !gShowDebugInfo;		
	}

	if ( !gKeys[VK_TAB] &&gShowDebugInfo )
	{
		gShowDebugInfoKey = false;
		gShowDebugInfo = !gShowDebugInfo;		
	}

	if ( gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.1f*gTimeScale;
	}

	if ( !gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.01f;
	}

	if ( !gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.01f;
	}

	if ( gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.1f*gTimeScale;
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
			Master::Instance().Release();
			gDone = !Master::Instance().LoadData(i + 1);
			RenderGL::Instance().SetGLLight();
		}
	}
}