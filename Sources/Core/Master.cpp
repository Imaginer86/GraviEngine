#include "Master.h"

#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

#include "Camera.h"
#include "../Constans.h"
#include "../Math/Color.h"
#include "../Render/RenderGL.h"

using namespace Core;

bool Master::gActive = false;
bool Master::gKeys[256];


//::Math::Color4f gLightAmbient( 0.8f, 0.8f, 0.8f, 1.0f );//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света

long Master::WndProc(  void*  hWnd,				// Дескриптор нужного окна
			 unsigned	uMsg,				// Сообщение для этого окна
			 unsigned	wParam,            // Дополнительная информация
			 unsigned	lParam)            // Дополнительная информация
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
			Render::RenderGL::Instance().ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// Младшее слово=Width, старшее слово=Height
			return 0;											// Возвращаемся
		}
	}
	// пересылаем все необработанные сообщения DefWindowProc
	return DefWindowProc( (HWND) hWnd, uMsg, wParam, lParam );
}

bool Master::Init(GameBase* gameBase_)
{
	gmGame = gameBase_;

	countUpdate = 1;
	countDraw = 1;

	// Создать наше OpenGL окно	
	bool assert = !Render::RenderGL::Instance().CreateWin( "Gravi Engine", gcWidth, gcHeight, 32);
	if (assert)
	{
		std::cerr << "CreateWin Failed!" << std::endl;
		return false;              // Выйти, если окно не может быть создано
	}

	return true;
}

void Master::Release()
{
	gmGame->Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
	Render::RenderGL::Instance().Release();						// Разрушаем окно
}

void Master::Run()
{
	unsigned lastTickCount = ::GetTickCount64();		// Get Tick Count
	unsigned tickCount, dtick, count;
	tickCount = 0, dtick = 0, count = 0;


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
				tickCount = ::GetTickCount64();			// Get The Tick Count
				UpdateKeys();
				
				if ( count > 1000 )
				{
					count -= 1000;
					gups = countUpdate;
					gfps = countDraw;					
					gtps = countTick;
					countUpdate = 0;
					countDraw  = 0;
					countTick = 0;
				}
				dtick = tickCount - lastTickCount;
				count += dtick;				
				Tick(dtick);				
				lastTickCount = tickCount;			// Set Last Count To Current Count
			}			
		}
	}
}

void Master::Tick(long dtick)
{
	unsigned i = 0;
	//for(i; i < UPR; ++i)
	if (!gPause)
	{
		for (i; i < UPF; ++i)
		{
			float dt = float(dtick) * TicksPerSrcond;
			Update(dt);
		}
	}
		
	//for(i; i < FPR; ++i)
	{
		Draw();
	}

	++countTick;
}

void Master::Update(float dt)
{	
	gTime += gTimeScale*dt;
	gmGame->Update(gTimeScale*dt);

	++countUpdate;
}


void Master::Draw()                // Здесь будет происходить вся прорисовка
{
	Render::RenderGL::Instance().BeginDraw();	
	gmGame->Draw();
	if (gShowDebugInfo)
	{
		Render::RenderGL::Instance().DrawDebugInfo();
	}
	Render::RenderGL::Instance().EndDraw();

	++countDraw;
}

void Master::UpdateKeys()
{
	if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
	{
		gDone = true;							// ESC говорит об останове выполнения программы
	}
	
	if( !gSwitchFullscreen && gKeys[VK_F1] )				// Была ли нажата F1?
	{
		gSwitchFullscreen = true;
		Render::RenderGL::Instance().Release();					// Разрушаем текущее окно
		Render::RenderGL::Instance().SetFullScreen( !Render::RenderGL::Instance().GetFullScreen() );		// Переключаем режим
		// Пересоздаём наше OpenGL окно
		//gDone = !Render::RenderGL::Instance().CreateWin((long*)Master::Instance().WndProc, ("NeHe OpenGL структура"), gcWidth, gcHeight, 32 );
		gDone = !Render::RenderGL::Instance().CreateWin(("NeHe OpenGL структура"), gcWidth, gcHeight, 32);
	}

	if (gSwitchFullscreen && !gKeys[VK_F1])
	{
		gSwitchFullscreen = false;
	}

	if( !gReloadKeyPress && gKeys[VK_F5])
	{
		gReloadKeyPress = true;

		gFirstLoad = true;
		Release();		
		gDone = !gmGame->LoadData(gmGame->GetSceneName());
		Init(gmGame);
		Render::RenderGL::Instance().SetGLLight();
	}

	if (gReloadKeyPress && !gKeys[VK_F5])
	{
		gReloadKeyPress = false;
	}

	if( !gSaveKeyPress && gKeys[VK_F6])
	{
		gSaveKeyPress = true;		

		gDone = !gmGame->SaveData("data/quickSave.dat");
	}

	if (gSaveKeyPress && !gKeys[VK_F6])
	{
		gSaveKeyPress = false;
	}

	if( !gLoadKeyPress && gKeys[VK_F9])
	{
		gLoadKeyPress = true;

		Release();
		gDone = !gmGame->LoadData("data/quickSave.dat");
		Render::RenderGL::Instance().SetGLLight();
	}

	if( gLoadKeyPress && !gKeys[VK_F9])
	{
		gLoadKeyPress = false;
	}
	
	if ( gKeys[VK_SPACE] )
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}

	if ( !gShowDebugInfoKey && gKeys[VK_TAB] )
	{	
		gShowDebugInfoKey = true;
		gShowDebugInfo = !gShowDebugInfo;		
	}

	if ( gShowDebugInfoKey && !gKeys[VK_TAB] )
	{
		gShowDebugInfoKey = false;
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
		if (Render::RenderGL::Instance().IsLight())					// Если не свет
		{
			Render::RenderGL::Instance().EnableLight();
		}
		else							// В противном случае
		{
			Render::RenderGL::Instance().DisableLight();
		}
	}

	if ( gLightOnKey && !gKeys['L'] )					// Клавиша 'L' Отжата?
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
		char c = '1' + i;
		if ( gKeys[c] )
		{
			gKeys[c] = false;
			gFirstLoad = true;
			Release();
			std::string fileName = "data/data";
			fileName += std::string(std::to_string(i + 1));
			fileName += ".dat";			
			gDone = !gmGame->LoadData(fileName);
			Init(gmGame);
			Render::RenderGL::Instance().SetGLLight();
		}
	}
}