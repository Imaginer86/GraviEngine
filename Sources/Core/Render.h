#pragma once
#include "../Types.h"
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

namespace Core
{
	class Render
	{
	protected:

		Render()
		{
		}

	public:

		virtual ~Render()
		{
		}

		//static Render& Instance()
		//{
			//static Render SingleRender;
			//return SingleRender;
		//}

		virtual bool Init() = 0;
		virtual bool Release() = 0;

		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;

		virtual void BuildFont() = 0;
		virtual void KillFont() = 0;

		virtual void ReSizeGLScene(unsigned width, unsigned height) = 0;
	
		virtual void SetGLLight() = 0;
		virtual int LoadGLTextures() = 0;

		//virtual void SetLight(const float32 *LightAmbient, const float32 *gLightDiffuse, const float32 *gLightPosition) = 0;

		virtual void EnableLight() = 0;
		virtual void DisableLight() = 0;

	
		virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits) = 0;

		virtual void glPrint(const char *fmt, ...) = 0;

		virtual void DrawDebugInfo() = 0;
		virtual void DrawBox(const Vector3f& pos, const Vector3f& size, const Vector3f& axic, const float32 angle, const ::Math::Color4f& color) const  = 0;
		virtual void DrawSphere(const Vector3f& pos, const float32 r, const ::Math::Color4f& color) const  = 0;

		virtual void SetLightOn(bool LightOn_) = 0;
		virtual bool GetLightOn() = 0;

		virtual void SetFullScreen(bool Fullscreen_) = 0;
		virtual bool GetFullScreen() = 0;
	};
}