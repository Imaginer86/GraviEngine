#include "Platform.h"

#include <Windows.h>

unsigned long Platform::GetTickCount()
{
	// Win
	return ::GetTickCount();
}

bool Platform::PeekMessage(MSG& msg)
{
	return bool(::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ));
}

void Platform::TranslateMessage( MSG& msg )
{
	::TranslateMessage(&msg);
}

void Platform::DispatchMessage( MSG& msg )
{
	::DispatchMessage(&msg);
}
