#pragma once
#include "../Math/Vector3.h"
#include "../Math/Color.h"

class Render
{
protected:

	Render()
	: LightOn(true)
	, Fullscreen(false)
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

	//virtual void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition) = 0;

	virtual void EnableLight() = 0;
	virtual void DisableLight() = 0;

	
	virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits) = 0;

	virtual void glPrint(const char *fmt, ...) = 0;

	virtual void DrawDebugInfo() = 0;
	virtual void DrawBox(const Vector3& pos, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const  = 0;
	virtual void DrawSphere(const Vector3& pos, const float r, const Color4f& color) const  = 0;

	void SetLightOn(bool LightOn_) { LightOn = LightOn_; }
	bool GetLightOn() { return LightOn; }

	void SetFullScreen(bool Fullscreen_) { Fullscreen = Fullscreen_; }
	bool GetFullScreen() { return Fullscreen;}

private:
	bool LightOn;      // Свет ВКЛ / ВЫКЛ
	bool Fullscreen;
};