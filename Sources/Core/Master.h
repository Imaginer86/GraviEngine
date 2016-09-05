#pragma once
#include <string>
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
		void Tick(unsigned long dtick);
		void Update(float dt);
		void Draw();
		void Release();
		void UpdateKeys();

		static long WndProc(void*  hWnd,	// Дескриптор нужного окна
			unsigned  uMsg,				// Сообщение для этого окна
			unsigned  wParam,            // Дополнительная информация
			unsigned  lParam);            // Дополнительная информация

		float GetGTime()
		{
			return gTime;
		}

		void SetGTimeScale(float gTimeScale_)
		{
			gTimeScale = gTimeScale_;
		}

		float GetGTimeScale()
		{
			return gTimeScale;
		}

		void SetUPR(unsigned UPR_)
		{
			UPR = UPR_;
		}

		void SetFPR(unsigned FPR_)
		{
			FPR = FPR_;
		}

		void SetUPF(unsigned UPF_)
		{
			UPF = UPF_;
		}

		unsigned GetUPF()
		{
			return UPF;
		}

		unsigned GetGTPS()
		{
			return gtps;
		}

		unsigned GetGFPS()
		{
			return gfps;
		}

		unsigned GetGUPS()
		{
			return gups;
		}

		void SetLightAmbient(const Math::Color4f& gLightAmbient_)
		{
			gLightAmbient = gLightAmbient_;
		}
		
		Math::Color4f GetLightAmient()
		{
			return gLightAmbient;
		}

		void SetLightDiffuse(const Math::Color4f& gLightDiffuse_)
		{
			gLightDiffuse = gLightDiffuse_;
		}

		Math::Color4f GetLightDiffuse()
		{
			return gLightDiffuse;
		}

		void SetLightPosition(const Math::Vector3f& gLightPosition_)
		{
			gLightPosition = gLightPosition_;
		}

		Math::Vector3f GetLightPosition()
		{
			return gLightPosition;
		}

		GameBase* GetGMGame()
		{
			return gmGame;
		}

		void SetGUpdateCamera(bool gUpdateCamera_)
		{
			gUpdateCamera = gUpdateCamera_;
		}

		bool GetGUpdateCamera()
		{
			return gUpdateCamera;
		}

		void SetGFirstLoad(bool gFirstLoad_)
		{
			gFirstLoad = gFirstLoad_;
		}
		bool GetGFirstLoad()
		{
			return gFirstLoad;
		}
	private:
		static bool gActive;                // Флаг активности окна
		static bool gKeys[256];					// Массив, используемый для операций с клавиатурой

		GameBase *gmGame;

		//Camera mCamera;		
		bool gDone;	// Логическая переменная для выхода из цикла
		bool gPause;
		bool gShowDebugInfo;		
		//bool gUpdateCamera = false;
		//bool gFirstLoad = false;

		//static unsigned gSceneNum;
		unsigned gSceneNumMax;
		unsigned countDraw, countUpdate, countTick;
		unsigned gfps, gups, gtps;
		unsigned FPR, UPR, UPF;

		float gTime;
		float gTimeScale;

		float gAngleScale;
		float gMoveScale;
		float gShiftScale;

		unsigned gcWidth;
		unsigned gcHeight;

		bool gUpdateCamera, gFirstLoad;		

		Math::Color4f gLightAmbient, gLightDiffuse;
		Math::Vector3f gLightPosition;     // Позиция света


		bool gLightOnKey;			// L нажата?
		bool gShowDebugInfoKey;		// TAB нажат?
		bool gReverseKeyPress;		// Q нажат?
		bool gSwitchFullscreen;		// F1 нажат?
		bool gReloadKeyPress;		// F5 нажат?
		bool gSaveKeyPress;			// F6 нажат?
		bool gLoadKeyPress;			// F9 нажат?

	};

	inline Master::Master()
	:gDone(false)	// Логическая переменная для выхода из цикла
	,gPause(true)
	,gShowDebugInfo(true)
	//,gUpdateCamera(false)
	//,gFirstLoad(false)
	,gSceneNumMax(9)
	,gTime(0.0)
	,gTimeScale(1.0)
	,gAngleScale(1.0)
	,gMoveScale(10.0)
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
	,gLightOnKey(false)
	,gShowDebugInfoKey(false)
	,gReverseKeyPress(false)
	,gSwitchFullscreen(false)
	,gReloadKeyPress(false)
	,gSaveKeyPress(false)
	,gLoadKeyPress(false)
	{
	}

	inline Master::~Master()
	{

	}
}