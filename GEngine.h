#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>
#endif

/*
// ����� ���������� C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
*/

#ifdef _WIN32
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#endif