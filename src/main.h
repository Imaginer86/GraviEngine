#pragma once
#include "Platform.h"

//unsigned long GetTickCount();
//bool PeekMessage(MSG &msg, HWND hWnd, unsigned int, unsigned int, unsigned int);

//#include "RenderGL.h"
//Render gRender = RenderGL::Instance();
//function GetTickCount() =  gRender::;



void Draw();
bool LoadData(unsigned fileNum);
void Release();
long WndProc(  HWND  hWnd,				// ���������� ������� ����
			 unsigned int  uMsg,				// ��������� ��� ����� ����
			 unsigned int  wParam,            // �������������� ����������
			 unsigned int  lParam);            // �������������� ����������
bool UpdateKeys();