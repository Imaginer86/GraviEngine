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

	bool PeekMessage(MSG& msg);			// ���� �� � ������� �����-������ ���������?

	void TranslateMessage( MSG& msg );		// ��������� ���������

	void DispatchMessage( MSG& msg );		// �������� ���������

	static long WndProc(  HWND  hWnd,				// ���������� ������� ����
						 UINT  uMsg,				// ��������� ��� ����� ����
						 WPARAM  wParam,            // �������������� ����������
						 LPARAM  lParam);            // �������������� ����������

private:
		Platform(){}
		virtual ~Platform(){}


};