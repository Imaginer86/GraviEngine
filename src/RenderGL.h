#include "Render.h"
#include "Camera.h"

#include <Windows.h>

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
	void BuildFont();
	void KillFont();
	int LoadGLTextures();
	void glPrint(const char *fmt, ...);
	void ReSizeGLScene(unsigned width, unsigned height);
	void SetGLLight();
	bool CreateGLWindow(WNDPROC WndProc, const char *title, unsigned width, unsigned height, int bits);

	void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition);

	void EnableLight();
	void DisableLight();

	void SetFullScreen(bool Fullscreen_);

	virtual bool Init();
	virtual bool Release();

	virtual void BeginDraw();
	virtual void EndDraw();

	virtual void DrawBox(const Vector3& pos, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const;
	virtual void DrawSphere(const Vector3& pos, const float r, const Color4f& color) const;


	HGLRC	hRC;              // Постоянный контекст рендеринга
	HDC		hDC;              // Приватный контекст устройства GDI
	HINSTANCE  rhInstance;              // Здесь будет хранится дескриптор приложения
	HWND	rhWnd;              // Здесь будет хранится дескриптор окна

	Camera *rCamera;

	float *rLightAmbient;//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
	float *rLightDiffuse;//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
	float *rLightPosition;//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

	bool LightOn;      // Свет ВКЛ / ВЫКЛ
	bool Fullscreen;
	bool ShowDebugInfo;

	unsigned *rSceneNum;
	float *rfps;
	float *rups;
	float *rTimeScale;
	float *rTime;
};