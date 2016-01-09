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
		void Tick();
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

		bool gKeys[256];					// Массив, используемый для операций с клавиатурой

		bool gActive;                // Флаг активности окна
		bool gDone;	// Логическая переменная для выхода из цикла
		bool gPause;
		bool gShowDebugInfo;		
		//bool gUpdateCamera = false;
		//bool gFirstLoad = false;
		
		//static unsigned gSceneNum;
		unsigned gSceneNumMax;

		float64 gTime;
		float64 gTimeScale;

		float64 gAngleScale;
		float64 gMoveScale;
		float64 gShiftScale;		

		unsigned countUpdate, countDraw;
		unsigned gfps, gups;
		unsigned FPR, UPR;

	private:
		//Camera mCamera;		
	};

	inline Master::Master()
	:gActive(true)                // Флаг активности окна
	,gDone(false)	// Логическая переменная для выхода из цикла
	,gPause(true)
	,gShowDebugInfo(true)
	//,gUpdateCamera(false)
	//,gFirstLoad(false)
	,gSceneNumMax(9)
	,gTime(0.0)
	,gTimeScale(1.0)
	,gAngleScale(1.0)
	,gMoveScale(1.0)
	,gShiftScale(1.0)
	,countUpdate(0)
	,countDraw(0)
	,gfps(60)
	,gups(100)
	,FPR(0)
	,UPR(0)
	{
	}

	inline Master::~Master()
	{

	}

}