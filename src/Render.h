#pragma once
#include "Math/Vector3.h"
#include "Color.h"

class Render
{
public:
	Render(){};
	virtual ~Render(){};

	static Render& Instance()
	{
		static Render SingleRender;
		return SingleRender;
	}

	virtual bool Init()
	{
		return false;
	}
	virtual bool Release()
	{
		return false;
	}

	virtual void BeginDraw(){}
	virtual void EndDraw(){}

	virtual void DrawBox(const Vector3& pos, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const {}
	virtual void DrawSphere(const Vector3& pos, const float r, const Color4f& color) const {}
};