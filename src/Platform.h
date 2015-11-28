#pragma once

#include <Windows.h>

class Platform
{
public:
	Platform(){}
	virtual ~Platform(){}

	unsigned long GetTickCount();		// Get Tick Count

	bool PeekMessage(MSG& msg);			// Есть ли в очереди какое-нибудь сообщение?

	void TranslateMessage( MSG& msg );		// Переводим сообщение

	void DispatchMessage( MSG& msg );		// Отсылаем сообщение
};