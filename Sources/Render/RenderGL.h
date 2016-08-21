#pragma once
#include "Render.h"

namespace Render
{
	class RenderGL : public Render
	{	
	public:
		RenderGL();

		static RenderGL& Instance()
		{
			static RenderGL SingleRender;
			return SingleRender;
		}

		virtual ~RenderGL();

		virtual bool Init();
		virtual bool Release();

		virtual void BeginDraw();
		virtual void EndDraw();

		virtual void BuildFont();
		virtual void KillFont();
	
		virtual void ReSizeGLScene(unsigned width, unsigned height);

		virtual void SetGLLight();

		virtual void EnableLight();
		virtual void DisableLight();

		virtual bool IsLight();

		//virtual void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition);

		virtual int LoadTextures();		

		virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits);

		virtual void Print(const char *fmt, ...);

		virtual void DrawDebugInfo();
		virtual void DrawTriangle(const Math::Vector3f& p1, const Math::Vector3f& p2, const Math::Vector3f& p3, const Math::Color4f& color) const;
		virtual void DrawPlane(const Math::Vector3f& pos, const Math::Vector2f& size, const Math::Vector3f& axic, const float angle, const Math::Color4f& color) const;
		virtual void DrawBox(const Math::Vector3f& pos, const Math::Vector3f& size, const Math::Vector3f& axic, const float angle, const Math::Color4f& color) const;
		virtual void DrawSphere(const Math::Vector3f& pos, const float r, const Math::Color4f& color) const;

		virtual void SetFullScreen(bool Fullscreen_) { Fullscreen = Fullscreen_; }
		virtual bool GetFullScreen() { return Fullscreen;}


	private:

		signed char *LoadTGA(const char *szFileName, int *iWidth, int *iHeight, int *iComponents, unsigned int *eFormat);
		bool LightOn;      // Свет ВКЛ / ВЫКЛ
		bool Fullscreen;
	};
}