#pragma once
#include <string>
//#include "../Camera.h"
#include "../GameBase.h"

namespace Core
{
	
	class Master
	{
	public:
		Master();
		virtual ~Master();

		static Master& Instance()
		{
			static Master TheSingleInstance;
			return TheSingleInstance;
		}

		void Init(GameBase* gameBase_);
		void Run();
		void Update();
		void Draw();
		void Release();
		void UpdateKeys();

		static long WndProc(void*  hWnd,	// Дескриптор нужного окна
			unsigned int  uMsg,				// Сообщение для этого окна
			unsigned int  wParam,            // Дополнительная информация
			unsigned int  lParam);            // Дополнительная информация

		bool Master::LoadData(unsigned fileNum);
		bool SaveData(const std::string& fileName);
	private:
		//Camera mCamera;		
	};

}