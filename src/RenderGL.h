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

	void BuildFont();
	void KillFont();
	int LoadGLTextures();
	void glPrint(const char *fmt, ...);
	virtual void ReSizeGLScene(unsigned width, unsigned height);
	virtual void SetGLLight();
	virtual bool CreateWin(long WndProc, const char *title, unsigned width, unsigned height, int bits);

	void SetLight(const float *LightAmbient, const float *gLightDiffuse, const float *gLightPosition);

	virtual void EnableLight();
	virtual void DisableLight();

	void SetFullScreen(bool Fullscreen_);

	virtual bool Init();
	virtual bool Release();

	virtual void BeginDraw();
	virtual void EndDraw();

	virtual void DrawDebugInfo();

	virtual void DrawBox(const Vector3& pos, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const;
	virtual void DrawSphere(const Vector3& pos, const float r, const Color4f& color) const;
};