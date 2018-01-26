#pragma once
#include "Render.h"
class RenderGL:	public Render
{
public:
	RenderGL() {}
	RenderGL(bool fullscreen_, bool light_, Vector3f cameraPos, Quaternion cameraQ);
	virtual ~RenderGL();

	virtual void init();
	virtual void resize(unsigned width, unsigned height);
	virtual bool createWindow(const char* title, unsigned width, unsigned height, unsigned char bits);
	virtual void killWindow();
	virtual void beginDraw() const;
	virtual void endDraw() const;

	virtual void buildFont();
	virtual void killFont();
	virtual void print(const Vector3f &pos, const char *fmt, ...);

	virtual void drawTriangleStrip(size_t n, const Vector3f *vertexs, const Vector3f* normals, const Color4f& color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d);
	virtual void drawQuad(const Vector3f *vertexs, const Vector3f& n, const Color4f &colors);
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axic, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const;
	virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const;
private:
	void setLight();
};

