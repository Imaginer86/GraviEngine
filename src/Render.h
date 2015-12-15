#pragma once
#include "Math/Vector3.h"
#include "Color.h"
#include "Camera.h"

//#include <Windows.h>


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

	virtual bool Init()
	{
		return false;
	}
	virtual bool Release()
	{
		return false;
	}

	virtual void BeginDraw() {}
	virtual void EndDraw() {}

	virtual void DrawDebugInfo() {}

	virtual void DrawBox(const Vector3& pos, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const {}
	virtual void DrawSphere(const Vector3& pos, const float r, const Color4f& color) const {}

	virtual void ReSizeGLScene(unsigned width, unsigned height)	{}
	virtual void SetGLLight() {}

	virtual void EnableLight() {}
	virtual void DisableLight() {}

	virtual bool CreateWin(long WndProc, const char *title, unsigned width, unsigned height, int bits) = 0;
//	{
//		return false;
//	}

public:

	Camera *rCamera;

	unsigned *rSceneNum;
	float *rfps;
	float *rups;
	float *rTimeScale;
	float *rTime;

	float *rLightAmbient;//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
	float *rLightDiffuse;//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
	float *rLightPosition;//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

	bool LightOn;      // Свет ВКЛ / ВЫКЛ
	bool Fullscreen;
};