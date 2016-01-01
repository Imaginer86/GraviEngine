﻿#pragma once
#include "Math/Vector3.h"
#include "Math/Color.h"

class Render
{
public:
	Render()
	: LightOn(true)
	, Fullscreen(false)
	{
	}

	virtual ~Render()
	{
	}

//	static Render& Instance()
//	{
//		static Render SingleRender;
//		return SingleRender;
//	}

	virtual bool Init() = 0;
	virtual bool Release() { return false; };

	virtual void BeginDraw() {};
	virtual void EndDraw() {};

	virtual void BuildFont() {};
	virtual void KillFont() {};

	virtual void ReSizeGLScene(unsigned width, unsigned height) {};
	virtual void SetGLLight() {};

	virtual int LoadGLTextures() { return 0; };

	//virtual void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition) = 0;

	virtual void EnableLight() {};
	virtual void DisableLight() {};

	virtual void SetFullScreen(bool Fullscreen_) {};

	virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits) { return false; };

	virtual void glPrint(const char *fmt, ...) {};

	virtual void DrawDebugInfo() {};
	virtual void DrawBox(const Vector3& pos, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const {};
	virtual void DrawSphere(const Vector3& pos, const float r, const Color4f& color) const {};

public:
	bool LightOn;      // Свет ВКЛ / ВЫКЛ
	bool Fullscreen;
};