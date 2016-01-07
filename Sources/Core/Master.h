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

		static bool gKeys[256];					// Массив, используемый для операций с клавиатурой
		//static unsigned gSceneNum;
		static unsigned gSceneNumMax;

		static float64 gTimeScale;
		static float64 gAngleScale;
		static float64 gMoveScale;
		static float64 gShiftScale;

		static bool gDone;	// Логическая переменная для выхода из цикла

		static bool gActive;                // Флаг активности окна
		static bool gPause;
		static bool gShowDebugInfo;
		//bool gUpdateCamera = false;
		//bool gFirstLoad = false;


		static float64 gfps;
		static float64 gups;
		static float64 gTime;

	private:
		//Camera mCamera;		
	};
}