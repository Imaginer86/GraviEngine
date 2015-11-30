#include "Input.h"

#include <Windows.h>

#include "RenderGL.h"
#include "Camera.h"

extern bool gKeys[256];
extern bool gPause;
extern bool gLightOnKey;

extern Render* mRender;
extern Camera mCamera;

extern float gTimeScale;
extern float gAngleScale;
extern float gMoveScale;
extern float gShiftScale;
extern bool gShowDebugInfoKey;		// TAB �����?
extern bool gShowDebugInfo;
extern bool gReverseKeyPress;		// Q �����?

extern unsigned gSceneNum;
extern unsigned gSceneNumMax;

extern bool LoadData(unsigned fileNum);
extern void Release();



bool Input::UpdateKeys()
{
	/*
	if( gKeys[VK_F1] )				// ���� �� ������ F1?
	{
		gKeys[VK_F1] = false;			// ���� ���, ������ �������� ������ ������� �� false
		mRender->Release();					// ��������� ������� ����
		mRender->Fullscreen = !mRender->Fullscreen;		// ����������� �����
		// ���������� ���� OpenGL ����
		if (!mRender->CreateWin(WndProc, ("NeHe OpenGL ���������"), gWidth, gHeight, 32 ))
		{
			return false;						// �������, ���� ��� ����������
		}
	} 
	*/
	if (gKeys[VK_SPACE])
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}

	if (gKeys['L'] && !gLightOnKey)			// ������� 'L' ������ � �� ������������?
	{
		gLightOnKey=true;						// lp ��������� TRUE
		mRender->LightOn=!mRender->LightOn;				// ������������ ����� TRUE/FALSE
		if (mRender->LightOn)					// ���� �� ����
		{
			mRender->EnableLight();
		}
		else							// � ��������� ������
		{
			mRender->DisableLight();
		}
	}
	if (!gKeys['L'])					// ������� 'L' ������?
	{
		gLightOnKey=false;						// ���� ���, �� lp ����� FALSE
	}

	if( gKeys[VK_F5])
	{
		gKeys[VK_F5] = false;
		Release();		
		if (!LoadData(gSceneNum))
			return false;
		mRender->SetGLLight();
	}

	for (unsigned i = 0; i < gSceneNumMax; i++)
	{
		char c = '1' + i;
		if (gKeys[c])
		{
			gKeys[c] = false;
			Release();
			if (!LoadData(i + 1))
				return false;
			mRender->SetGLLight();
		}
	}

	if( gKeys[VK_RIGHT])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateLR(gAngleScale*gTimeScale);
		else
			mCamera.RotateLR(gShiftScale*gAngleScale*gTimeScale);				
	}

	if( gKeys[VK_LEFT])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateLR(-gAngleScale*gTimeScale);			
		else
			mCamera.RotateLR(-gShiftScale*gAngleScale*gTimeScale);			
	}

	if( gKeys[VK_UP])
	{								
		if (gKeys[VK_SHIFT])
			mCamera.RotateUpDown(gAngleScale*gTimeScale);
		else
			mCamera.RotateUpDown(gShiftScale*gAngleScale*gTimeScale);
	}

	if( gKeys[VK_DOWN])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateUpDown(-gAngleScale*gTimeScale);
		else
			mCamera.RotateUpDown(-gShiftScale*gAngleScale*gTimeScale);
	}

	if( gKeys['W'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(-gMoveScale*gTimeScale);
		else
			mCamera.MoveCamera(-gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['S']) 
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(gMoveScale*gTimeScale);
		else
			mCamera.MoveCamera(gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['A'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(gMoveScale*gTimeScale);
		else
			mCamera.MoveLRCamera(gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['D'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(-gMoveScale*gTimeScale);
		else
			mCamera.MoveLRCamera(-gShiftScale*gMoveScale*gTimeScale);
	}

	if (gKeys[VK_TAB] && !gShowDebugInfoKey)
	{
		gShowDebugInfoKey = true;
		gShowDebugInfo = !gShowDebugInfo;
	}

	if (!gKeys[VK_TAB])
		gShowDebugInfoKey = false;

	if ( gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.1f*gTimeScale;
	}

	else if ( gKeys[VK_ADD] )
	{
		gTimeScale += 0.01f;
	}

	if ( gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.1f*gTimeScale;
	}

	else if ( gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.01f;
	}

	if (gKeys[VK_SHIFT] && gKeys['0'])
	{
		gTimeScale = -1.0f;
	}

	else if (gKeys['0'])
	{
		gTimeScale = 0.0f;
	}

	if( gKeys['R'])
	{
		gTimeScale = 1.0f;
	}

	if( gKeys['Q'] && !gReverseKeyPress)
	{
		gTimeScale = -gTimeScale;
		gReverseKeyPress = true;
	}
	if (!gKeys['Q'] && gReverseKeyPress )
	{
		gReverseKeyPress = false;
	}

	return true;

}