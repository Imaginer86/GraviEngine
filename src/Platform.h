#pragma once

#include <Windows.h>

class Platform
{
public:
	Platform(){}
	virtual ~Platform(){}

	unsigned long GetTickCount();		// Get Tick Count

	bool PeekMessage(MSG& msg);			// ���� �� � ������� �����-������ ���������?

	void TranslateMessage( MSG& msg );		// ��������� ���������

	void DispatchMessage( MSG& msg );		// �������� ���������
};