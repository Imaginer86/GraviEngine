#include "Platform.h"
#include <Windows.h>


//using namespace win;


// #define PM_NOREMOVE         0x0000
// #define PM_REMOVE           0x0001
// #define PM_NOYIELD          0x0002
// #if(WINVER >= 0x0500)
// #define PM_QS_INPUT         (QS_INPUT << 16)
// #define PM_QS_POSTMESSAGE   ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
// #define PM_QS_PAINT         (QS_PAINT << 16)
// #define PM_QS_SENDMESSAGE   (QS_SENDMESSAGE << 16)
// #endif /* WINVER >= 0x0500 */


long Platform::GetTickCount()
{
	return ::GetTickCount();
}

//bool Platform::PeekMessageCCC(void *msg, void *hWnd, unsigned int wParam, unsigned lParam, unsigned int XZ)
//bool Platform::PeekMessageCCC(MSG &msg, HWND hWnd, unsigned int wParam, unsigned lParam, unsigned int XZ)
//{
//	HWND* hWnd_ = (HWND*) hWnd;
//	MSG& msg_ = (MSG&) msg;
//	return ::PeekMessage(&msg_, *hWnd_, wParam, lParam, XZ);
//}