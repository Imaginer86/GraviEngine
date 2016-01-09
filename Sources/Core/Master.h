#pragma once
#include <string>
#include "../Types.h"
#include "../GameBase.h"
#include "../Math/Color.h"

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

		bool Init(GameBase* gameBase_);
		void Run();
		void Tick(long dtick);
		void Update(float32 dt);
		void Draw();
		void Release();
		void UpdateKeys();

		static long WndProc(void*  hWnd,	// Дескриптор нужного окна
			unsigned  uMsg,				// Сообщение для этого окна
			unsigned  wParam,            // Дополнительная информация
			unsigned  lParam);            // Дополнительная информация

		static bool gActive;                // Флаг активности окна
		static bool gKeys[256];					// Массив, используемый для операций с клавиатурой

		bool gDone;	// Логическая переменная для выхода из цикла
		bool gPause;
		bool gShowDebugInfo;		
		//bool gUpdateCamera = false;
		//bool gFirstLoad = false;
		
		//static unsigned gSceneNum;
		unsigned gSceneNumMax;

		float32 gTime;
		float32 gTimeScale;

		float32 gAngleScale;
		float32 gMoveScale;
		float32 gShiftScale;		

		unsigned countDraw, countUpdate, countTick;
		unsigned gfps, gups, gtps;
		unsigned FPR, UPR, UPF;

		unsigned gcWidth;
		unsigned gcHeight;

		bool gUpdateCamera, gFirstLoad;

		GameBase *gmGame;

		::Math::Color4f gLightAmbient, gLightDiffuse;
		Vector3f gLightPosition;     // Позиция света
	private:
		//Camera mCamera;		
	};

	inline Master::Master()
	//:gActive(true)                // Флаг активности окна
	:gDone(false)	// Логическая переменная для выхода из цикла
	,gPause(false)
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
	,countTick(0)
	,gfps(60)
	,gups(100)
	,gtps(0)
	,UPF(0)
	,FPR(0)
	,UPR(0)
	,gcWidth(1920)
	,gcHeight(1080)
	,gUpdateCamera(false)
	,gFirstLoad(true)
	,gLightAmbient( 0.8f, 0.8f, 0.8f, 1.0f )
	,gLightDiffuse( 0.5f, 0.5f, 0.5f, 1.0f )
	,gLightPosition( 0.0f, 10.0f, 0.0f)
	{
	}

	inline Master::~Master()
	{

	}
}