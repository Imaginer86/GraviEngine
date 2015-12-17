#pragma once
#include <Windows.h>

//namespace win{


/*
struct HHHWND
{
	int hhhWnd;
	unsigned int Msg;
};

struct PPPOINT
{
	long	x;
	long	y;
};

struct MMMSG
{
	HHHWND			hwnd;
	PPPOINT			pt;
	unsigned int	message;
	unsigned int	wParam;
	unsigned int	lParam;
	unsigned long	time;	

};

#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002
*/

//typedef HWND HHHWND;
//typedef MSG MMMSG;
//typedef *MSG (*MMMSG);


class Platform
{
public:
	Platform(){}
	virtual ~Platform(){}

	static const Platform& Instance()
	{
		static Platform TheSingleInstance;
		return TheSingleInstance;
	}

	long GetTickCount();
	bool PeekMessageCCC(MSG &msg, HWND hWnd, unsigned int, unsigned int, unsigned int);
};

//}