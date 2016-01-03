#include "GameBase.h"
#include "Core/Master.h"

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

	GameBase::Instance().LoadData(1);
	// Init
	Core::Master::Instance().Init(&GameBase::Instance());

	// Run
	Core::Master::Instance().Run();

	// Shutdown
	Core::Master::Instance().Release();

	return 0;
}