#pragma once

#include <Windows.h>

class Platform
{
public:

	static const Platform& Instance()
	{
		static Platform TheSingleInstance;
		return TheSingleInstance;
	}

	unsigned long GetTickCount();		// Get Tick Count

	bool PeekMessage(MSG& msg);			// Есть ли в очереди какое-нибудь сообщение?

	void TranslateMessage( MSG& msg );		// Переводим сообщение

	void DispatchMessage( MSG& msg );		// Отсылаем сообщение

	static long WndProc(  HWND  hWnd,				// Дескриптор нужного окна
						 UINT  uMsg,				// Сообщение для этого окна
						 WPARAM  wParam,            // Дополнительная информация
						 LPARAM  lParam);            // Дополнительная информация

private:
		Platform(){}
		virtual ~Platform(){}


};