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

		virtual int LoadGLTextures();
	
		//virtual void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition);

		virtual void EnableLight();
		virtual void DisableLight();

		virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits);

		virtual void glPrint(const char *fmt, ...);

		virtual void DrawDebugInfo();
		virtual void DrawTriangle(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const ::Math::Color4f& color) const;
		virtual void DrawPlane(const Vector3f& pos, const Vector2f& size, const Vector3f& axic, const float angle, const ::Math::Color4f& color) const;
		virtual void DrawBox(const Vector3f& pos, const Vector3f& size, const Vector3f& axic, const float angle, const ::Math::Color4f& color) const;
		virtual void DrawSphere(const Vector3f& pos, const float r, const ::Math::Color4f& color) const;

		virtual void SetLightOn(bool LightOn_) { LightOn = LightOn_; }
		virtual bool GetLightOn() { return LightOn; }

		virtual void SetFullScreen(bool Fullscreen_) { Fullscreen = Fullscreen_; }
		virtual bool GetFullScreen() { return Fullscreen;}


	private:
		bool LightOn;      // Свет ВКЛ / ВЫКЛ
		bool Fullscreen;
	};
}