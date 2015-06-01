#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>

#include <Windows.h>
					   

#include "Game.h"
#include "Camera.h"
#include "Color.h"

#include "Math\Math.h"

#include "RenderGL.h"




/*
** RGB Image Structure
*/

//typedef struct _AUX_RGBImageRec {
    //GLint sizeX, sizeY;
    //unsigned char *data;
//} AUX_RGBImageRec;



//#define auxDIBImageLoad auxDIBImageLoadA

//AUX_RGBImageRec * APIENTRY auxDIBImageLoadA(LPCSTR);


/*
#define auxDIBImageLoad auxDIBImageLoadA

AUX_RGBImageRec * APIENTRY auxDIBImageLoadA(LPCSTR);
AUX_RGBImageRec * APIENTRY auxDIBImageLoadW(LPCWSTR);
*/

//HWND	hWnd = nullptr;              // Здесь будет хранится дескриптор окна



const int gWidth = 1600;
const int gHeight = 900;

bool  gKeys[256];                // Массив, используемый для операций с клавиатурой
bool gLightOnKey = false;         // L нажата?
bool gShowDebugInfoKey = false;		// TAB нажат?
bool  gActive = true;                // Флаг активности окна, установленный в true по умолчанию

bool  gPause = true;


float gTimeScale = 1.0f;
float gTime = 0.0f;

float gAngleScale = 1.0f;
float gMoveScale = 1.0f;
float gShiftScale = 0.1f;

float gfps = 0.0f;
float gups = 0.0f;

unsigned gSceneNum = 1;
unsigned gSceneNumMax = 7;

float gLightAmbient[4];//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
float gLightDiffuse[4];//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
float gLightPosition[4];//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

bool gUpdateCamera = true;
Game mGame;
Camera mCamera;
RenderGL mRender;




	//GLfloat		xrot		=  0.0f;						// X Rotation
	//GLfloat		yrot		=  0.0f;						// Y Rotation
	//GLfloat		xrotspeed	=  0.01f;						// X Rotation Speed
	//GLfloat		yrotspeed	=  0.0f;						// Y Rotation Speed


//AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
//{
//	std::ifstream File(Filename, std::ios::in);
//	if (File)											// Does The File Exist?
//	{
//		File.close();
//		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
//	}

//	return NULL;										// If Load Failed Return NULL
//}






LRESULT  CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );        // Прототип функции WndProc

//float angle_ = 0.0f;

void DrawGLScene()                // Здесь будет происходить вся прорисовка
{	  
	mRender.BeginDraw();
	mGame.Draw();
	mRender.EndDraw();
	
	

	/*	glRotatef(xrot, 1.0f, 0.0f, 0.0f);					// Rotate On The X Axis
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);					// Rotate On The Y Axis

		xrot += xrotspeed;									// Update X Rotation Angle By xrotspeed
	yrot += yrotspeed;									// Update Y Rotation Angle By yrotspeed

	


		glColor3f(1.0f, 1.0f, 1.0f);						// Set Color To White
	//glBindTexture(GL_TEXTURE_2D, texture[1]);			// Select Texture 2 (1)
	//gluSphere(q, 0.35f, 32, 16);						// Draw First Sphere

	glBindTexture(GL_TEXTURE_2D, texture[3]);			// Select Texture 3 (2)
	//glColor4f(1.0f, 1.0f, 1.0f, 0.4f);					// Set Color To White With 40% Alpha
	//glEnable(GL_BLEND);									// Enable Blending
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set Blending Mode To Mix Based On SRC Alpha
	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping

	gluSphere(q, 0.35f, 32, 16);						// Draw Another Sphere Using New Texture
														// Textures Will Mix Creating A MultiTexture Effect (Reflection)
	//glDisable(GL_TEXTURE_GEN_S);						// Disable Sphere Mapping
	//glDisable(GL_TEXTURE_GEN_T);						// Disable Sphere Mapping
	//glDisable(GL_BLEND);								// Disable Blending
	*/

	
	//return true;

// 	glTranslatef(mCamera.pos.x, mCamera.pos.y, mCamera.pos.z);
// 	glRotatef(mCamera.angle.x, 1, 0, 0);
// 	glRotatef(mCamera.angle.y, 0, 1, 0);
// 	glRotatef(mCamera.angle.z, 0, 0, 1);
// 	glTranslatef(mCamera.pos.x, mCamera.pos.y, mCamera.pos.z);

//		GLenum light = GL_LIGHT0;
// 		if (mGame.Entities[i].isLight) {
// 			glDisable(GL_LIGHTING);
// 			GLfloat massLight[] = {mGame.Entities[i].color.r, mGame.Entities[i].color.g,mGame.Entities[i].color.b,mGame.Entities[i].color.a,};
// 			GLfloat massPos[] = {mGame.Entities[i].pos.x, mGame.Entities[i].pos.y, mGame.Entities[i].pos.z, 1.0f};
// 			glLightfv(light ,GL_DIFFUSE, massLight);
// 			glLightfv(light ,GL_POSITION, massPos);            
// 			glEnable(light);
// 			light++;
// 		}

	
}


void Release()
{
	mGame.Release();
	gTime = 0.0f;
	gTimeScale = 1.0f;
}
bool LoadData(unsigned fileNum)
{
	gSceneNum = fileNum;

	std::string fileNumstr = std::to_string(fileNum);
	std::string fileName = "data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);	
	if ( !dataFile )
		return false;

	Vector3 cameraPos;
	Vector3 cameraAxic;
	float cameraAngle;

	dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z
		>> cameraAxic.x >> cameraAxic.y >> cameraAxic.z 
		>> cameraAngle;
	dataFile >> gUpdateCamera;

	if (gUpdateCamera)
	{
		mCamera.SetPos(cameraPos);
		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		if (cameraAngle > 0.0f)
		{
			q.normalize();
		}
		mCamera.SetQuaternion(q);
	}

	dataFile >> gLightAmbient[0] >> gLightAmbient[1] >> gLightAmbient[2] >> gLightAmbient[3];
	dataFile >> gLightDiffuse[0] >> gLightDiffuse[1] >> gLightDiffuse[2] >> gLightDiffuse[3];
	dataFile >> gLightPosition[0] >> gLightPosition[1] >> gLightPosition[2] >> gLightPosition[3];

	mRender.rLightAmbient = gLightAmbient;
	mRender.rLightDiffuse= gLightDiffuse;
	mRender.rLightPosition = gLightPosition;
	

	Vector3 graviAcc;

	dataFile >> graviAcc.x >> graviAcc.y >> graviAcc.z;
	mGame.SetGraviAcc(graviAcc);

	unsigned int numEntities = 0;

	dataFile >> numEntities;

	mGame.SetNumEntities(numEntities);

	int numMass = 0;

	dataFile >>  numMass;

	//mGame.SetNumMasses(numMass);

	for(int i = 0; i < numMass; i++) {
		float m = 0.0f, r = 0.0f;
		Vector3 pos, vel;
		//bool isLight = false;
		Color4f color(0.0f, 0.0f, 0.0f, 0.0f);
		dataFile >> m >> r 
			>> pos.x >> pos.y >> pos.z 
			>> vel.x >> vel.y >> vel.z
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetMass(m, r, pos, vel, /*isLight,*/ color);        
	}

	int numBoxs = 0;
	dataFile >> numBoxs;

	//mGame.SetNumBoxes(numBoxs);
	for(int i = 0; i < numBoxs; i++) {
		float m = 0.0;
		Vector3 pos, size, vel;
		Color4f color;
		Quaternion q;
		Quaternion qVel;
		float angle, angleVel;
		Vector3 angleAxic, angleVelAxic;
		dataFile >> m 			
			>> size.x >> size.y >> size.z
			>> pos.x >> pos.y >> pos.z
			>> vel.x >> vel.y >> vel.z
			//>> q.x >> q.y >> q.z >> q.w
			//>> qVel.x >> qVel.y >> qVel.z >> qVel.w
			>> q.x >> q.y >> q.z >> angle
			>> qVel.x >> qVel.y >> qVel.z >> angleVel
			//>> angleAxic.x >> angleAxic.y >> angleAxic.z >> angle
			//>> angleVelAxic.x >> angleVelAxic.y >> angleVelAxic.z >> angleVel
			>> color.r >> color.g >> color.b >> color.a;
		//angleAxic.unitize();
		//angleVelAxic.unitize();
		angle = Math::degreesToRadians(angle);
		angleVel = Math::degreesToRadians(angleVel);
		q.w = cosf(angle / 2.0f);
		q.x *= sinf(angle / 2.0f);
		q.y *= sinf(angle / 2.0f);
		q.z *= sinf(angle / 2.0f);

		//q.x = angleAxic.x*sinf(angle / 2.0f);
		//q.y = angleAxic.y*sinf(angle / 2.0f);
		//q.z = angleAxic.z*sinf(angle / 2.0f);

		qVel.w = cosf(angleVel / 2.0f);
		qVel.x *= sinf(angleVel / 2.0f);
		qVel.y *= sinf(angleVel / 2.0f);
		qVel.z *= sinf(angleVel / 2.0f);

		//qVel.x = angleVelAxic.x*sinf(angleVel / 2.0f);
		//qVel.y = angleVelAxic.y*sinf(angleVel / 2.0f);
		//qVel.z = angleVelAxic.z*sinf(angleVel / 2.0f);
		//q.normalize();
		//qVel.normalize();
		mGame.SetBox(m, size, pos, vel, q, qVel, color);
	}

/*	int numLines = 0;
	//dataFile >> numLines;
	//mGame.SetNumLines(numLines);
	for(int i = 0; i < numLines; i++) {
		float m = 0.0f, r = 0.0f, h = 0.0f;
		Vector3 pos;
		Color4f color;
		Quaternion q;
		Vector3 u;
		float w = 0.0f;
		dataFile >> m >> r >> h
			>> pos.x >> pos.y >> pos.z
			>> u.x >> u.y >> u.z >> w
			>> color.r >> color.g >> color.b >> color.a;
		q.fromAxisAngle(u, w);
		mGame.SetLine(m, r, h, pos, q, color);
	}
*/

	dataFile.close();
	return true;
}


bool UpdateKeys()
{
	if (gKeys[VK_SPACE])
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}
	if (gKeys['L'] && !gLightOnKey)			// Клавиша 'L' нажата и не удерживается?
	{
		gLightOnKey=true;						// lp присвоили TRUE
		mRender.LightOn=!mRender.LightOn;				// Переключение света TRUE/FALSE
		if (mRender.LightOn)					// Если не свет
		{
			mRender.EnableLight();
		}
		else							// В противном случае
		{
			mRender.DisableLight();
		}
	}
	if (!gKeys['L'])					// Клавиша 'L' Отжата?
	{
		gLightOnKey=false;						// Если так, то lp равно FALSE
	}

	if( gKeys[VK_F1] )				// Была ли нажата F1?
	{
		gKeys[VK_F1] = false;			// Если так, меняем значение ячейки массива на false
		mRender.Release();					// Разрушаем текущее окно
		mRender.Fullscreen = !mRender.Fullscreen;		// Переключаем режим
		// Пересоздаём наше OpenGL окно
		if (!mRender.CreateGLWindow(WndProc, ("NeHe OpenGL структура"), gWidth, gHeight, 32 ))
		{
			return false;						// Выходим, если это невозможно
		}
	} 

	if( gKeys[VK_F5])
	{
		gKeys[VK_F5] = false;
		Release();		
		if (!LoadData(gSceneNum))
			return false;
		mRender.SetGLLight();
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
			mRender.SetGLLight();
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
			mCamera.MoveCamera(gMoveScale*gTimeScale);
		else
			mCamera.MoveCamera(gShiftScale*gMoveScale*gTimeScale);
	}
	if( gKeys['S']) 
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(-gMoveScale*gTimeScale);
		else
			mCamera.MoveCamera(-gShiftScale*gMoveScale*gTimeScale);
	}
	if( gKeys['A'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(-gMoveScale*gTimeScale);
		else
			mCamera.MoveLRCamera(-gShiftScale*gMoveScale*gTimeScale);
	}
	if( gKeys['D'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(gMoveScale*gTimeScale);
		else
			mCamera.MoveLRCamera(gShiftScale*gMoveScale*gTimeScale);
	}
	if (gKeys[VK_TAB] && !gShowDebugInfoKey)
	{
		gShowDebugInfoKey = true;		
		mRender.ShowDebugInfo = !mRender.ShowDebugInfo;
	}
	if (!gKeys[VK_TAB])
		gShowDebugInfoKey = false;
	if (gKeys[VK_ADD])
		gTimeScale += 0.01f;
	if (gKeys[VK_SUBTRACT])
		gTimeScale -= 0.01f;
	if (gKeys['0'])
		gTimeScale = 1.0f;

	return true;
}

LRESULT CALLBACK WndProc(  HWND  hWnd,				// Дескриптор нужного окна
						 UINT  uMsg,				// Сообщение для этого окна
						 WPARAM  wParam,            // Дополнительная информация
						 LPARAM  lParam)            // Дополнительная информация
{
	switch (uMsg)                // Проверка сообщения для окна
	{
	case WM_ACTIVATE:            // Проверка сообщения активности окна
		{
			if( !HIWORD( wParam ) )          // Проверить состояние минимизации
			{
				gActive = true;					// Программа активна
			}
			else
			{
				gActive = false;					// Программа теперь не активна
			}

			return 0;						// Возвращаемся в цикл обработки сообщений
		}
	case WM_SYSCOMMAND:            // Перехватываем системную команду
		{
			switch ( wParam )            // Останавливаем системный вызов
			{
			case SC_SCREENSAVE:				// Пытается ли запустится скринсейвер?
			case SC_MONITORPOWER:			// Пытается ли монитор перейти в режим сбережения энергии?
				return 0;						// Предотвращаем это
			}
			break;              // Выход
		}
	case WM_CLOSE:              // Мы получили сообщение о закрытие?
		{
			PostQuitMessage( 0 );			// Отправить сообщение о выходе
			return 0;							// Вернуться назад
		}

	case WM_KEYDOWN:            // Была ли нажата кнопка?
		{
			gKeys[wParam] = true;			// Если так, мы присваиваем этой ячейке true
			return 0;							// Возвращаемся
		}
	case WM_KEYUP:              // Была ли отпущена клавиша?
		{
			gKeys[wParam] = false;			//  Если так, мы присваиваем этой ячейке false
			return 0;						// Возвращаемся
		}
	case WM_SIZE:              // Изменены размеры OpenGL окна
		{
			mRender.ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// Младшее слово=Width, старшее слово=Height
			return 0;											// Возвращаемся
		}
	}
	// пересылаем все необработанные сообщения DefWindowProc
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


int WINAPI WinMain(	HINSTANCE  hInstance,				// Дескриптор приложения
					HINSTANCE  hPrevInstance,			// Дескриптор родительского приложения
					LPSTR    lpCmdLine,					// Параметры командной строки
					int    nCmdShow )					// Состояние отображения окна
{
	mRender.rhInstance = hInstance;
	//mRender.rhWnd = hWnd;
	mRender.rCamera = &mCamera;
	mRender.rSceneNum = &gSceneNum;
	mRender.rfps = &gfps;
	mRender.rups = &gups;
	mRender.rTimeScale = &gTimeScale;
	mRender.rTime = &gTime;
	MSG  msg;           // Структура для хранения сообщения Windows
	
	bool  done = false;	// Логическая переменная для выхода из цикла

	DWORD tickCount = 0;
	DWORD lastTickCount = 0;

	// Спрашивает пользователя, какой режим экрана он предпочитает
	//if( MessageBox( NULL, "Хотите ли Вы запустить приложение в полноэкранном режиме?",  "Запустить в полноэкранном режиме?", MB_YESNO | MB_ICONQUESTION) == IDNO )
	//{
		//fullscreen = false;          // Оконный режим
	//


	if (!LoadData(gSceneNum)) {
		MessageBox (NULL, "Load Data Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 1;													// Return False (Failure)
	}

	// Создать наше OpenGL окно
	if (!mRender.CreateGLWindow(WndProc, "NeHe OpenGL окно", gWidth, gHeight, 32))
	{
		return 1;              // Выйти, если окно не может быть создано
	}

	lastTickCount = GetTickCount ();		// Get Tick Count
	float framesPerSecond = 0.0f	;
	float lastTime = 0.0f;

	while( !done )							// Цикл продолжается, пока done не равно true
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )    // Есть ли в очереди какое-нибудь сообщение?
		{
			if( msg.message == WM_QUIT )						// Мы поучили сообщение о выходе?
			{
				done = true;										// Если так, done=true
			}
			else												// Если нет, обрабатывает сообщения
			{
				TranslateMessage( &msg );							// Переводим сообщение
				DispatchMessage( &msg );							// Отсылаем сообщение
			}
		}
		else	// Если нет сообщений
		{
				// Прорисовываем сцену.
			if( gActive )          // Активна ли программа?
			{
				//else            // Не время для выхода, обновим экран.
				{
					//--------------------------------
					{
						tickCount = GetTickCount();				// Get The Tick Count

						if (!gPause)
						{				
							gTime += gTimeScale*float(tickCount - lastTickCount)/1000.0f;
							mGame.Update(gTimeScale*float(tickCount - lastTickCount)/1000.0f );
						} 					
						framesPerSecond++;
						float currentTime = ((float)tickCount)*0.001f;
						if ((currentTime - lastTime) > 1.0f)
						{
							lastTime = currentTime;
							gfps = framesPerSecond;
							framesPerSecond = 0.0f;
						}
						lastTickCount = tickCount;			// Set Last Count To Current Count
						DrawGLScene();						// Рисуем сцену
						
					}

					if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
					{
						done = true;							// ESC говорит об останове выполнения программы
					}
					if (!UpdateKeys())
					{
						done = true;
						MessageBox(NULL, "Uodate Keys Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
					}
				}
			}
		}
	}

	// Shutdown
	mRender.Release();						// Разрушаем окно
	return ( msg.wParam );              // Выходим из программы
}