#pragma once
#include <string>

class Master
{
public:
	Master(){}
	virtual ~Master(){}

	static Master& Instance()
	{
		static Master TheSingleInstance;
		return TheSingleInstance;
	}

	static long WndProc(void*  hWnd,				// Дескриптор нужного окна
		unsigned int  uMsg,				// Сообщение для этого окна
		unsigned int  wParam,            // Дополнительная информация
		unsigned int  lParam);            // Дополнительная информация

	static bool Master::LoadData(unsigned fileNum);
	bool SaveData(const std::string& fileName);

	void Run();
	void Update();
	void Draw();
	void Release();
};