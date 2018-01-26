#pragma once
#include "Vector3f.h"
#include "Quaternion.h"
#include "Color4f.h"
#include "Camera.h"

class Render
{
protected:
	bool	fullscreen;
	bool	lightOn;
	Camera	camera;
public:
	Render() {};
	Render(bool fullscreen_, bool light_, Vector3f cameraPos, Quaternion cameraQ);
	virtual ~Render() {};

	virtual void init() = 0;
	virtual void resize(unsigned width, unsigned height) = 0;
	virtual bool createWindow(const char* title, unsigned width, unsigned height, unsigned char bits) = 0;	
	virtual void killWindow() = 0;
	virtual void setFullscreen(bool fullscreen_) { fullscreen = fullscreen_; }

	virtual void buildFont() = 0;
	virtual void killFont() = 0;
	virtual void print(const Vector3f &pos, const char *fmt, ...) = 0;

	virtual void beginDraw() const = 0;
	virtual void endDraw() const = 0;

	virtual void drawTriangleStrip(size_t n, const Vector3f *vertexs, const Vector3f* normals, const Color4f& color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d) = 0;
	virtual void drawQuad(const Vector3f *vertexs, const Vector3f& n, const Color4f &colors) = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axic, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const = 0;
	virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const = 0;

	void RotateCamera(const Quaternion &q);
	void MoveCamera(const Vector3f &v);
	void MoveCameraQ(float s);

	//Camera& GetCamera() { return camera; }
};

inline Render::Render(bool fullscreen_, bool light_, Vector3f cameraPos, Quaternion cameraQ)
: fullscreen(fullscreen_)
, lightOn(light_)
, camera(cameraPos, cameraQ)
{
	//camera.q *= Quaternion(90, Vector3f(1.0f, 0.0f, 0.0f));
	//camera.q *= Quaternion(180, Vector3f(0.0f, 1.0f, 0.0f));

}

inline void Render::RotateCamera(const Quaternion &q)
{
	camera.q *= q;
	camera.q.normalize();
}

inline void Render::MoveCamera(const Vector3f &v)
{
	camera.pos += v;
}

inline void Render::MoveCameraQ(float s)
{
	Vector3f dif(0.0f, 0.0f, -1.0f);
	camera.q.rotate(dif);
	dif *= s;
	camera.pos += dif;
}