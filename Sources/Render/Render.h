﻿#pragma once
#include "../Math/Vector2f.h"
#include "../Math/Vector3f.h"
#include "../Math/Color.h"

namespace Render
{
	class Render
	{
	public:

		Render(){}

		virtual ~Render(){}

		virtual bool Init() = 0;
		virtual bool Release() = 0;

		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;

		virtual void BuildFont() = 0;
		virtual void KillFont() = 0;

		virtual void ReSizeGLScene(unsigned width, unsigned height) = 0;
	
		virtual void SetGLLight() = 0;

		virtual void EnableLight() = 0;
		virtual void DisableLight() = 0;

		virtual bool IsLight() = 0;

		//virtual void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition) = 0;

		virtual int LoadTextures() = 0;

		virtual bool CreateWin(long* WndProc, const char *title, unsigned width, unsigned height, int bits) = 0;

		virtual void Print(const char *fmt, ...) = 0;

		virtual void DrawDebugInfo() = 0;
		virtual void DrawTriangle(const Math::Vector3f& p1, const Math::Vector3f& p2, const Math::Vector3f& p3, const ::Math::Color4f& color) const = 0;
		virtual void DrawPlane(const Math::Vector3f& pos, const Math::Vector2f& size, const Math::Vector3f& axic, const float angle, const Math::Color4f& color) const = 0;
		virtual void DrawBox(const Math::Vector3f& pos, const Math::Vector3f& size, const Math::Vector3f& axic, const float angle, const Math::Color4f& color) const  = 0;
		virtual void DrawSphere(const Math::Vector3f& pos, const float r, const Math::Color4f& color) const  = 0;

		virtual void SetFullScreen(bool Fullscreen_) = 0;
		virtual bool GetFullScreen() = 0;
	};
}