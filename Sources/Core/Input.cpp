#include "Input.h"
#include "Defines.h"

#include "Render.h"
#include "Master.h"

#include "../Camera.h"
#include "../Constans.h"

using namespace Core;

extern bool gKeys[256];
extern bool gPause;
extern bool gLightOnKey;
extern bool gUpdateKeyPress;


extern float gTimeScale;
extern float gAngleScale;
extern float gMoveScale;
extern float gShiftScale;
extern bool gShowDebugInfo;
extern bool gShowDebugInfoKey;		// TAB нажат?

extern bool gReverseKeyPress;		// Q нажат?

//extern bool gSaveKeyPress;

extern unsigned gSceneNum;
extern unsigned gSceneNumMax;

extern bool  done;

extern Render* gmRender;


void Input::UpdateKeys()
{
	
	if( gKeys[VK_F1] )				// Была ли нажата F1?
	{
		gKeys[VK_F1] = false;			// Если так, меняем значение ячейки массива на false
		gmRender->Release();					// Разрушаем текущее окно
		gmRender->SetFullScreen( !gmRender->GetFullScreen() );		// Переключаем режим
		// Пересоздаём наше OpenGL окно
		done = !gmRender->CreateWin((long*)Master::Instance().WndProc, ("NeHe OpenGL структура"), gcWidth, gcHeight, 32 );
	}

	if( gUpdateKeyPress && gKeys[VK_F5] == true )
	{
		gKeys[VK_F5] = false;
		gUpdateKeyPress = true;
		Master::Instance().Release();		
		done = !Master::Instance().LoadData(gSceneNum);
		gmRender->SetGLLight();
	}

	if ( gUpdateKeyPress && gKeys[VK_F6] == true )
	{
		gKeys[VK_F6] = false;
		gUpdateKeyPress = false;
		Master::Instance().Release();
		done = !Master::Instance().SaveData("dataSave");
	}

	if ( !gUpdateKeyPress && gKeys[VK_F6] == false )
	{
		gUpdateKeyPress = true;
	}

	if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
	{
		done = true;							// ESC говорит об останове выполнения программы
	}
	
	if ( gKeys[VK_SPACE] )
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}

	if( gKeys[VK_RIGHT] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateLR(gAngleScale*gTimeScale);
		else
			Camera::Instance().RotateLR(gShiftScale*gAngleScale*gTimeScale);				
	}

	if( gKeys[VK_LEFT] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateLR(-gAngleScale*gTimeScale);			
		else
			Camera::Instance().RotateLR(-gShiftScale*gAngleScale*gTimeScale);			
	}

	if( gKeys[VK_UP] )
	{								
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateUpDown(gAngleScale*gTimeScale);
		else
			Camera::Instance().RotateUpDown(gShiftScale*gAngleScale*gTimeScale);
	}

	if( gKeys[VK_DOWN] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().RotateUpDown(-gAngleScale*gTimeScale);
		else
			Camera::Instance().RotateUpDown(-gShiftScale*gAngleScale*gTimeScale);
	}

	if ( gKeys[VK_TAB] && !gShowDebugInfoKey )
	{
		gShowDebugInfoKey = true;
		gShowDebugInfo = !gShowDebugInfo;		
	}

	if ( !gKeys[VK_TAB] &&gShowDebugInfo )
	{
		gShowDebugInfoKey = false;
		gShowDebugInfo = !gShowDebugInfo;		
	}

	if ( gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.1f*gTimeScale;
	}

	if ( !gKeys[VK_SHIFT] && gKeys[VK_ADD] )
	{
		gTimeScale += 0.01f;
	}

	if ( !gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.01f;
	}

	if ( gKeys[VK_SHIFT] && gKeys[VK_SUBTRACT] )
	{
		gTimeScale -= 0.1f*gTimeScale;
	}	

	if ( gKeys[VK_SHIFT] && gKeys['0'] )
	{
		gTimeScale = -1.0f;
	}
	else if ( gKeys['0'] )
	{
		gTimeScale = 0.0f;
	}

	if( gKeys['W'] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveCamera(-gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveCamera(-gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['S'] ) 
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveCamera(gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveCamera(gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['A'] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveLRCamera(gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveLRCamera(gShiftScale*gMoveScale*gTimeScale);
	}

	if( gKeys['D'] )
	{
		if (gKeys[VK_SHIFT])
			Camera::Instance().MoveLRCamera(-gMoveScale*gTimeScale);
		else
			Camera::Instance().MoveLRCamera(-gShiftScale*gMoveScale*gTimeScale);
	}

	if ( gKeys['L'] && !gLightOnKey )			// Клавиша 'L' нажата и не удерживается?
	{
		gLightOnKey=true;						// lp присвоили TRUE
		gmRender->SetLightOn(!gmRender->GetLightOn());				// Переключение света TRUE/FALSE
		if (gmRender->GetLightOn())					// Если не свет
		{
			gmRender->EnableLight();
		}
		else							// В противном случае
		{
			gmRender->DisableLight();
		}
	}

	if ( !gKeys['L'] )					// Клавиша 'L' Отжата?
	{
		gLightOnKey=false;						// Если так, то lp равно FALSE
	}

	if( gKeys['R'] )
	{
		gTimeScale = 1.0f;
	}

	if( gKeys['Q'] && !gReverseKeyPress )
	{
		gTimeScale = -gTimeScale;
		gReverseKeyPress = true;
	}

	if ( !gKeys['Q'] && gReverseKeyPress )
	{
		gReverseKeyPress = false;
	}
	
	for (unsigned char i = 0; i < gSceneNumMax; i++)
	{
		unsigned char c = '1' + i;
		if ( gKeys[c] )
		{
			gKeys[c] = false;
			Master::Instance().Release();
			done = !Master::Instance().LoadData(i + 1);
			gmRender->SetGLLight();
		}
	}
}