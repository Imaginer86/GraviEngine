#include <iostream>
#include <string>

#include "main.h"


#include "Master.h"
#include "Platform.h"
#include "RenderGL.h"
#include "Game.h"

#include "Camera.h"
#include "Input.h"

#include "Math/Math.h"

#include "Color.h"


const int gWidth = 1600;
const int gHeight = 900;


bool gLightOnKey = false;			// L нажата?
bool gShowDebugInfo = true;
bool gShowDebugInfoKey = false;		// TAB нажат?
//bool gShowResetKey = false;			// R нажат?
bool gReverseKeyPress = false;		// Q нажат?
bool gUpdateKeyPress = false;
bool gSaveKeyPress = false;

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

unsigned gSceneNum = 1;
unsigned gSceneNumMax = 9;

float gLightAmbient[4];//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
float gLightDiffuse[4];//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
float gLightPosition[4];//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

bool gUpdateCamera = false;
bool gFirstLoad = true;



//LRESULT  CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );        // Прототип функции WndProc

//long WndProc(  HWND  hWnd,				// Дескриптор нужного окна
						 //UINT  uMsg,				// Сообщение для этого окна
						 //WPARAM  wParam,            // Дополнительная информация
						 //LPARAM  lParam);            // Дополнительная информация



//int WINAPI WinMain(	HINSTANCE  hInstance,				// Дескриптор приложения
//					HINSTANCE  hPrevInstance,			// Дескриптор родительского приложения
//					LPSTR    lpCmdLine,					// Параметры командной строки
//					int    nCmdShow */)					// Состояние отображения окна
int main()
{
	std::cout << "Hello" << std::endl;
	std::cerr << "And Your Hello" << std::endl;

	//mRender->rhInstance = hInstance;
	//mRender.rhWnd = hWnd;
	//RenderGL::Instance().rCamera = &mCamera;
	RenderGL::Instance().rSceneNum = &gSceneNum;
	RenderGL::Instance().rfps = &gfps;
	RenderGL::Instance().rups = &gups;
	RenderGL::Instance().rTimeScale = &gTimeScale;
	RenderGL::Instance().rTime = &gTime;

	if (!Master::Instance().LoadData(gSceneNum)) 
	{
		//MessageBox (NULL, "Load Data Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		std::cerr << "Load Data Failed!" << std::endl;
		return 1;													// Return False (Failure)
	}



	// Создать наше OpenGL окно
	
	if (!RenderGL::Instance().CreateWin( (long*)Master::Instance().WndProc, "Gravi Engine", gWidth, gHeight, 32))
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
	


	Master::Instance().Run();

	// Shutdown
	RenderGL::Instance().Release();						// Разрушаем окно
	
	//return ( int(msg.wParam) );              // Выходим из программы

	return 0;
}


