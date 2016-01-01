#include <iostream>
#include <string>

#include "Master.h"

#include "Math/Math.h"
#include "Math/Color.h"


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

bool gUpdateCamera = false;
bool gFirstLoad = true;

Color4f gLightAmbient( 0.8f, 0.8f, 0.8f, 1.0f );//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
Color4f gLightDiffuse( 1.0f, 1.0f, 1.0f, 1.0f );//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
Color4f gLightPosition( 3.0f, 3.0f, 4.0f, 1.0f );//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

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

	// Спрашивает пользователя, какой режим экрана он предпочитает
	//if( MessageBox( NULL, "Хотите ли Вы запустить приложение в полноэкранном режиме?",  "Запустить в полноэкранном режиме?", MB_YESNO | MB_ICONQUESTION) == IDNO )
	//{		
		//fullscreen = false;          // Оконный режим
	//}
	//
	//std::cout  << "Хотите ли Вы запустить приложение в полноэкранном режиме? Y/N? " << std::endl;	

	// Init
	Master::Instance().Init();

	// Run
	Master::Instance().Run();

	// Shutdown
	Master::Instance().Release();

	return 0;
}