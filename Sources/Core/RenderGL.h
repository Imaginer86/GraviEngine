#pragma once
#include "Render.h"

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
	
	//virtual void SetLight(const float64 *LightAmbient, const float64 *gLightDiffuse, const float64 *gLightPosition);

	virtual void EnableLight();
	virtual void DisableLight();

	virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits);

	virtual void glPrint(const char *fmt, ...);

	virtual void DrawDebugInfo();

	virtual void DrawBox(const Vector3d& pos, const Vector3d& size, const Vector3d& axic, const float64 angle, const Color4f& color) const;

	virtual void DrawSphere(const Vector3d& pos, const float64 r, const Color4f& color) const;

	virtual void SetLightOn(bool LightOn_) { LightOn = LightOn_; }
	virtual bool GetLightOn() { return LightOn; }

	virtual void SetFullScreen(bool Fullscreen_) { Fullscreen = Fullscreen_; }
	virtual bool GetFullScreen() { return Fullscreen;}


private:
	bool LightOn;      // Свет ВКЛ / ВЫКЛ
	bool Fullscreen;
};