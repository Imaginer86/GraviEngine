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

long Platform::WndProc(  HWND  hWnd,				// ���������� ������� ����
						 UINT  uMsg,				// ��������� ��� ����� ����
						 WPARAM  wParam,            // �������������� ����������
						 LPARAM  lParam)            // �������������� ����������
{
	switch (uMsg)                // �������� ��������� ��� ����
	{
	case WM_ACTIVATE:            // �������� ��������� ���������� ����
		{
			if( !HIWORD( wParam ) )          // ��������� ��������� �����������
			{
				gActive = true;					// ��������� �������
			}
			else
			{
				gActive = false;					// ��������� ������ �� �������
			}

			return 0;						// ������������ � ���� ��������� ���������
		}
	case WM_SYSCOMMAND:            // ������������� ��������� �������
		{
			switch ( wParam )            // ������������� ��������� �����
			{
			case SC_SCREENSAVE:				// �������� �� ���������� �����������?
			case SC_MONITORPOWER:			// �������� �� ������� ������� � ����� ���������� �������?
				return 0;						// ������������� ���
			}
			break;              // �����
		}
	case WM_CLOSE:              // �� �������� ��������� � ��������?
		{
			PostQuitMessage( 0 );			// ��������� ��������� � ������
			return 0;							// ��������� �����
		}

	case WM_KEYDOWN:            // ���� �� ������ ������?
		{
			gKeys[wParam] = true;			// ���� ���, �� ����������� ���� ������ true
			return 0;							// ������������
		}
	case WM_KEYUP:              // ���� �� �������� �������?
		{
			gKeys[wParam] = false;			//  ���� ���, �� ����������� ���� ������ false
			return 0;						// ������������
		}
	case WM_SIZE:              // �������� ������� OpenGL ����
		{
			mRender->ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// ������� �����=Width, ������� �����=Height
			return 0;											// ������������
		}
	}
	// ���������� ��� �������������� ��������� DefWindowProc
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
