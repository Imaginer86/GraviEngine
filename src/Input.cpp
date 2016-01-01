#include "Input.h"

#include <string>
#include <Windows.h>

#include "RenderGL.h"
#include "Camera.h"
#include "Master.h"

extern bool gKeys[256];
extern bool gPause;
extern bool gLightOnKey;

//extern RenderGL* mRender;
//extern Camera mCamera;

extern float gTimeScale;
extern float gAngleScale;
extern float gMoveScale;
extern float gShiftScale;
extern bool gShowDebugInfoKey;		// TAB нажат?
extern bool gShowDebugInfo;
extern bool gReverseKeyPress;		// Q нажат?
extern bool gUpdateKeyPress;
extern bool gSaveKeyPress;

extern unsigned gSceneNum;
extern unsigned gSceneNumMax;

bool Input::UpdateKeys()
{
	/*
	if( gKeys[VK_F1] )				// Была ли нажата F1?
	{
		gKeys[VK_F1] = false;			// Если так, меняем значение ячейки массива на false
		mRender->Release();					// Разрушаем текущее окно
		mRender->Fullscreen = !mRender->Fullscreen;		// Переключаем режим
		// Пересоздаём наше OpenGL окно
		if (!mRender->CreateWin(WndProc, ("NeHe OpenGL структура"), gWidth, gHeight, 32 ))
		{
			return false;						// Выходим, если это невозможно
		}
	} 
	*/
	if (gKeys[VK_SPACE])
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}

	if (gKeys['L'] && !gLightOnKey)			// Клавиша 'L' нажата и не удерживается?
	{
		gLightOnKey=true;						// lp присвоили TRUE
		RenderGL::Instance().LightOn=!RenderGL::Instance().LightOn;				// Переключение света TRUE/FALSE
		if (RenderGL::Instance().LightOn)					// Если не свет
		{
			RenderGL::Instance().EnableLight();
		}
		else							// В противном случае
		{
			RenderGL::Instance().DisableLight();
		}
	}
	if (!gKeys['L'])					// Клавиша 'L' Отжата?
	{
		gLightOnKey=false;						// Если так, то lp равно FALSE
	}

	if(gUpdateKeyPress && gKeys[VK_F5] == true)
	{
		gKeys[VK_F5] = false;
		gUpdateKeyPress = true;
		Master::Instance().Release();		
		if (!Master::Instance().LoadData(gSceneNum))
			return false;
		RenderGL::Instance().SetGLLight();
	}

	if (gUpdateKeyPress && gKeys[VK_F6] == true)
	{
		gKeys[VK_F5] = false;
		gUpdateKeyPress = false;
		Master::Instance().Release();
		if (!Master::Instance().SaveData("dataSave"))
			return false;	
	}

	if (!gUpdateKeyPress && gKeys[VK_F6] == false)
	{
		gUpdateKeyPress = true;
	}

	for (unsigned i = 0; i < gSceneNumMax; i++)
	{
		char c = '1' + i;
		if (gKeys[c])
		{
			gKeys[c] = false;
			Master::Instance().Release();
			if (!Master::Instance().LoadData(i + 1))
				return false;
			RenderGL::Instance().SetGLLight();
		}
	}

	if( gKeys[VK_RIGHT])
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateLR(gAngleScale*gTimeScale);
		else
			Camera::Instance().RotateLR(gShiftScale*gAngleScale*gTimeScale);				
	}

	if( gKeys[VK_LEFT])
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateLR(-gAngleScale*gTimeScale);			
		else
			Camera::Instance().RotateLR(-gShiftScale*gAngleScale*gTimeScale);			
	}

	if( gKeys[VK_UP])
	{								
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateUpDown(gAngleScale*gTimeScale);
		else
			Camera::Instance().RotateUpDown(gShiftScale*gAngleScale*gTimeScale);
	}

	if( gKeys[VK_DOWN])
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateUpDown(-gAngleScale*gTimeScale);
		else
			Camera::Instance().RotateUpDown(-gShiftScale*gAngleScale*gTimeScale);
	}

	if( gKeys['W'])
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveCamera(-gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveCamera(-gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['S']) 
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveCamera(gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveCamera(gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['A'])
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveLRCamera(gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveLRCamera(gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['D'])
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveLRCamera(-gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveLRCamera(-gShiftScale*gMoveScale*gTimeScale);
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