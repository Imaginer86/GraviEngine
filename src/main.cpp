#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
//#include "GL\glaux.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Game.h"
#include "Camera.h"
#include "Color.h"


HGLRC	hRC	 = NULL;              // Постоянный контекст рендеринга
HDC		hDC  = NULL;              // Приватный контекст устройства GDI
HWND	hWnd = NULL;              // Здесь будет хранится дескриптор окна
HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения 


/*
** RGB Image Structure
*/

typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char *data;
} AUX_RGBImageRec;



#define auxDIBImageLoad auxDIBImageLoadA

//AUX_RGBImageRec * APIENTRY auxDIBImageLoadA(LPCSTR);


/*
#define auxDIBImageLoad auxDIBImageLoadA

AUX_RGBImageRec * APIENTRY auxDIBImageLoadA(LPCSTR);
AUX_RGBImageRec * APIENTRY auxDIBImageLoadW(LPCWSTR);
*/



const int gWidth = 1600;
const int gHeight = 900;

bool  gKeys[256];                // Массив, используемый для операций с клавиатурой
bool  gActive = true;                // Флаг активности окна, установленный в true по умолчанию

bool  gPause = true;

bool gLightOn = true;      // Свет ВКЛ / ВЫКЛ
bool gLightOnKey = false;         // L нажата?

bool gShowDebugInfo = true;
bool gShowDebugInfoKey = false;

bool  gFullscreen = false;              // Флаг режима окна, установленный в полноэкранный по умолчанию

float gTimeScale = 1.0f;
float gTime = 0.0f;

float gAngleScale = 1.0f;
float gMoveScale = 1.0f;

float fps = 0.0f;
float ups = 0.0f;

unsigned SceneNum = 1;

Game mGame;
Camera mCamera;

GLfloat gLightAmbient[4];//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
GLfloat gLightDiffuse[4];//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
GLfloat gLightPosition[4];//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

GLYPHMETRICSFLOAT gmFont[256];	// Storage For Information About Our Outline Font Characters
GLuint	gFontBase;				// Base Display List For The Font Set
GLuint		texture[4];									// 3 Textures

GLUquadricObj	*q;										// Quadratic For Drawing A Sphere



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

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    int Status=FALSE;									// Status Indicator

	return Status;	

/*
    AUX_RGBImageRec *TextureImage[4];					// Create Storage Space For The Textures
    memset(TextureImage,0,sizeof(void *)*3);			// Set The Pointer To NULL
    if ((TextureImage[0]=LoadBMP("EnvWall.bmp")) &&// Load The Floor Texture
        (TextureImage[1]=LoadBMP("Ball.bmp")) &&	// Load the Light Texture
        (TextureImage[2]=LoadBMP("EnvRoll.bmp")) &&	// Load the Wall Texture
		(TextureImage[3] = LoadBMP("EarthMap_2500x1250.bmp")) )
	{   
		Status=TRUE;									// Set The Status To TRUE
		glGenTextures(4, &texture[0]);					// Create The Texture
		for (int loop=0; loop<4; loop++)				// Loop Through 5 Textures
		{
			glBindTexture(GL_TEXTURE_2D, texture[loop]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		for (INT loop=0; loop<4; loop++)					// Loop Through 5 Textures
		{
			if (TextureImage[loop])						// If Texture Exists
			{
				if (TextureImage[loop]->data)			// If Texture Image Exists
				{
					free(TextureImage[loop]->data);		// Free The Texture Image Memory
				}
				free(TextureImage[loop]);				// Free The Image Structure 
			}
		}
	}
	return Status;										// Return The Status
*/
}

GLvoid BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID

	gFontBase = glGenLists(256);								// Storage For 256 Characters

	font = CreateFont(	
		-20,							// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_BOLD,						// Font Weight
		TRUE,							// Italic
		TRUE,							// Underline
		TRUE,							// Strikeout
			//SYMBOL_CHARSET,					// Character Set Identifier
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
			//"Comic Sans MS"				// Font Name
		"Arial"							// Font Name
		);				

	SelectObject(hDC, font);							// Selects The Font We Created

	wglUseFontOutlines(	hDC,							// Select The Current DC
		0,								// Starting Character
		255,							// Number Of Display Lists To Build
		gFontBase,							// Starting Display Lists
		0.0f,							// Deviation From The True Outlines
		0.1f,							// Font Thickness In The Z Direction
		WGL_FONT_POLYGONS,			// Use Polygons, Not Lines
		//WGL_FONT_LINES,					// Use Polygons, Not Lines
		gmFont);							// Address Of Buffer To Recieve Data
}

GLvoid KillFont(GLvoid)									// Delete The Font
{
	glDeleteLists(gFontBase, 256);								// Delete All 256 Characters
}

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	float		length=0;								// Used To Find The Length Of The Text
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	for (unsigned int loop=0;loop<(strlen(text));loop++)	// Loop To Find Text Length
	{
		length+=gmFont[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}

	glPushMatrix();
	//glTranslatef(-length/2,0.0f,0.0f);					// Center Our Text On The Screen
	//glPushAttrib(GL_ALL_ATTRIB_BITS);							// Pushes The Display List Bits
	glListBase(gFontBase);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
	glPopMatrix();
}

LRESULT  CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );        // Прототип функции WndProc


GLvoid ReSizeGLScene( GLsizei width, GLsizei height )        // Изменить размер и инициализировать окно GL
{
	if( height == 0 )              // Предотвращение деления на ноль
	{
		height = 1;
	}

	glViewport( 0, 0, width, height );          // Сброс текущей области вывода

	glMatrixMode( GL_PROJECTION );            // Выбор матрицы проекций
	glLoadIdentity();              // Сброс матрицы проекции

	// Вычисление соотношения геометрических размеров для окна
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0, 400.0);

// 	glMatrixMode( GL_MODELVIEW );            // Выбор матрицы вида модели
// 	gluLookAt(mCamera.pos.x, mCamera.pos.y, mCamera.pos.z, 
// 		mCamera.pos.x, mCamera.pos.y, mCamera.pos.z + 50, 
// 		0, 100, 0);
// 
// 	//glTranslatef(0.0f, 0.0f, -60.0f);
// 	glLoadIdentity();              // Сброс матрицы вида модели
}

void SetGLLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, gLightAmbient);    // Установка Фонового Света
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gLightDiffuse);    // Установка Диффузного Света
	glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);   // Позиция света
	glEnable(GL_LIGHT0); // Разрешение источника света номер один
	if (gLightOn)
		glEnable(GL_LIGHTING);
}


bool InitGL( GLvoid )                // Все установки касаемо OpenGL происходят здесь
{
	//if (!LoadGLTextures())								// If Loading The Textures Failed
//	{
//		return FALSE;									// Return False
//	}
	glShadeModel( GL_SMOOTH );            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth( 1.0f );              // Разрешить очистку буфера глубины
	glEnable( GL_DEPTH_TEST );            // Разрешить тест глубины
	glDepthFunc( GL_LEQUAL );            // Тип теста глубины
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );      // Улучшение в вычислении перспективы
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);

	SetGLLight();	

	BuildFont();				// Build The Font

	q = gluNewQuadric();								// Create A New Quadratic
	gluQuadricNormals(q, GL_SMOOTH);					// Generate Smooth Normals For The Quad
	gluQuadricTexture(q, GL_TRUE);						// Enable Texture Coords For The Quad

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping

	return true;                // Инициализация прошла успешно
}


GLvoid KillGLWindow( GLvoid )              // Корректное разрушение окна
{
	if( gFullscreen )              // Мы в полноэкранном режиме?
	{
		ChangeDisplaySettings( NULL, 0 );        // Если да, то переключаемся обратно в оконный режим
		ShowCursor( true );            // Показать курсор мышки
	}
	if( hRC )                // Существует ли Контекст Рендеринга?
	{
		if( !wglMakeCurrent( NULL, NULL ) )        // Возможно ли освободить RC и DC?
		{
			MessageBox( NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		if( !wglDeleteContext( hRC ) )        // Возможно ли удалить RC?
		{
			MessageBox( NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		hRC = NULL;              // Установить RC в NULL
	}
	if( hDC && !ReleaseDC( hWnd, hDC ) )          // Возможно ли уничтожить DC?
	{
		MessageBox( NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hDC=NULL;                // Установить DC в NULL
	}
	if(hWnd && !DestroyWindow(hWnd))            // Возможно ли уничтожить окно?
	{
		MessageBox( NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hWnd = NULL;                // Установить hWnd в NULL
	}
	if( !UnregisterClass( "OpenGL", hInstance ) )        // Возможно ли разрегистрировать класс
	{
		MessageBox( NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                // Установить hInstance в NULL
	}

	KillFont();
}


BOOL CreateGLWindow( LPCSTR title, int width, int height, int bits, bool fullscreenflag )
{
	GLuint		PixelFormat;			    // Хранит результат после поиска
	WNDCLASS	wc;						   // Структура класса окна
	DWORD		dwExStyle;				  // Расширенный стиль окна
	DWORD		dwStyle;				 // Обычный стиль окна

	RECT WindowRect;                       // Grabs Rectangle Upper Left / Lower Right Values

	WindowRect.left = 0L;					    	  // Установить левую составляющую в 0
	WindowRect.right = long(width);                  // Установить правую составляющую в Width
	WindowRect.top = 0L;					    	// Установить верхнюю составляющую в 0
	WindowRect.bottom = long(height);              // Установить нижнюю составляющую в Height

	gFullscreen = fullscreenflag;              // Устанавливаем значение глобальной переменной fullscreen

	hInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;					  // Процедура обработки сообщений
	wc.cbClsExtra		= 0;									 // Нет дополнительной информации для окна
	wc.cbWndExtra		= 0;							 	    // Нет дополнительной информации для окна
	wc.hInstance		= hInstance;						   // Устанавливаем дескриптор
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);       // Загружаем указатель мышки
	wc.hbrBackground	= NULL;								// Фон не требуется для GL
	wc.lpszMenuName		= NULL;							   // Меню в окне не будет
	wc.lpszClassName	= "OpenGL";						  // Устанавливаем имя классу

	if( !RegisterClass( &wc ) )              // Пытаемся зарегистрировать класс окна
	{
		MessageBox( NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // Выход и возвращение функцией значения false
	}

	if( gFullscreen )                // Полноэкранный режим?
	{
		DEVMODE dmScreenSettings;            // Режим устройства
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );    // Очистка для хранения установок

		dmScreenSettings.dmSize=sizeof( dmScreenSettings );      // Размер структуры Devmode
		dmScreenSettings.dmPelsWidth  =   width;				// Ширина экрана
		dmScreenSettings.dmPelsHeight  =   height;			   // Высота экрана
		dmScreenSettings.dmBitsPerPel  =   bits;			  // Глубина цвета
		dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя

		// Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
		if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
			if( MessageBox( NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES )
			{
				gFullscreen = false;          // Выбор оконного режима (fullscreen = false)
			}
			else
			{
				// Выскакивающее окно, сообщающее пользователю о закрытие окна.
				MessageBox( NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP );
				return false;            // Выход и возвращение функцией false
			}
		}
	}

	if(gFullscreen)                  // Мы остались в полноэкранном режиме?
	{
		dwExStyle  =   WS_EX_APPWINDOW;      // Расширенный стиль окна
		dwStyle    =   WS_POPUP;            // Обычный стиль окна
		ShowCursor( false );               // Скрыть указатель мышки
	}
	else
	{
		dwExStyle  =   WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;       // Расширенный стиль окна
		dwStyle    =   WS_OVERLAPPEDWINDOW;						// Обычный стиль окна
	}

	AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );      // Подбирает окну подходящие размеры

	if( !( hWnd = CreateWindowEx(  
		dwExStyle,										// Расширенный стиль для окна
		("OpenGL"),									   // Имя класса
		title,										  // Заголовок окна
		WS_CLIPSIBLINGS |							 // Требуемый стиль для окна
		WS_CLIPCHILDREN |							// Требуемый стиль для окна
		dwStyle,								   // Выбираемые стили для окна
		0, 0,									  // Позиция окна
		WindowRect.right-WindowRect.left,		 // Вычисление подходящей ширины
		WindowRect.bottom-WindowRect.top,		// Вычисление подходящей высоты
		NULL,								   // Нет родительского
		NULL,								  // Нет меню
		hInstance,							 // Дескриптор приложения
		NULL ) ) )							// Не передаём ничего до WM_CREATE (???)
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // Вернуть false
	}

	static  PIXELFORMATDESCRIPTOR pfd=              // pfd сообщает Windows каким будет вывод на экран каждого пикселя
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // Размер дескриптора данного формата пикселей
		1,										 // Номер версии
		PFD_DRAW_TO_WINDOW |					// Формат для Окна
		PFD_SUPPORT_OPENGL |				   // Формат для OpenGL
		PFD_DOUBLEBUFFER,					  // Формат для двойного буфера
		PFD_TYPE_RGBA,						 // Требуется RGBA формат
		BYTE(bits),								// Выбирается бит глубины цвета
		0, 0, 0, 0, 0, 0,				   // Игнорирование цветовых битов
		0,								  // Нет буфера прозрачности
		0,								 // Сдвиговый бит игнорируется
		0,								// Нет буфера накопления
		0, 0, 0, 0,					   // Биты накопления игнорируются
		32,							  // 32 битный Z-буфер (буфер глубины)
		0,							 // Нет буфера трафарета
		0,							// Нет вспомогательных буферов
		PFD_MAIN_PLANE,            // Главный слой рисования
		0,						  // Зарезервировано
		0, 0, 0                  // Маски слоя игнорируются
	};

	if( !( hDC = GetDC( hWnd ) ) )              // Можем ли мы получить Контекст Устройства?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // Вернуть false
	}

	if( !( PixelFormat = ChoosePixelFormat( hDC, &pfd ) ) )        // Найден ли подходящий формат пикселя?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // Вернуть false
	}

	if( !SetPixelFormat( hDC, PixelFormat, &pfd ))          // Возможно ли установить Формат Пикселя?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // Вернуть false
	}

	if( !( hRC = wglCreateContext( hDC ) ) ) // Возможно ли установить Контекст Рендеринга?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	if( !wglMakeCurrent( hDC, hRC ) )            // Попробовать активировать Контекст Рендеринга
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // Вернуть false
	}

	ShowWindow( hWnd, SW_SHOW );				  // Показать окно
	SetForegroundWindow( hWnd );				 // Слегка повысим приоритет
	SetFocus( hWnd );							// Установить фокус клавиатуры на наше окно
	ReSizeGLScene( width, height );			   // Настроим перспективу для нашего OpenGL экрана.

	if( !InitGL() )                  // Инициализация только что созданного окна
	{
		KillGLWindow();                // Восстановить экран
		MessageBox( NULL, ("Initialization Failed."), ("ERROR"), MB_OK | MB_ICONEXCLAMATION );
		return false;                // Вернуть false
	}

	return true;                  // Всё в порядке!
}


//float angle_ = 0.0f;

void DrawGLScene()                // Здесь будет происходить вся прорисовка
{	  
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );      // Очистить экран и буфер глубины	
	glMatrixMode(GL_MODELVIEW);								  // Выбор матрицы вида модели
	glLoadIdentity();										 // Сбросить текущую матрицу

	//gluLookAt(mCamera.GetPos().x, mCamera.GetPos().y, mCamera.GetPos().z, 
	//mCamera.GetView().x, mCamera.GetView().y, mCamera.GetView().z, 
		//mCamera.GetUp().x, mCamera.GetUp().y, mCamera.GetUp().z);

	Quaternion q = mCamera.GetQuaternion();
	Vector3 cameraAxic;
	float cameraAngle;
	q.toAxisAngle(cameraAxic, cameraAngle);
	glRotatef(cameraAngle, cameraAxic.x, cameraAxic.y, cameraAxic.z);

	Vector3 cameraPos = mCamera.GetPos();
	glTranslatef(-cameraPos.x, -cameraPos.y, -cameraPos.z);


	SetGLLight();
	mGame.Draw();

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

	if (gShowDebugInfo)
	{
		glLoadIdentity();
		glPushMatrix();
		glColor3f(1, 1, 1);		
		glTranslatef(-5.0f, 3.6f, -10.0f);	
		glScalef(0.2f, 0.2f, 0.2f);		
		glPrint("Scene #: %d", SceneNum);
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("FPS: %2.2f", fps);						// Print GL Text To The Screen
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("UPS: %2.2f", ups);
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("Time: %2.2f", gTime);
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("Time Scale: %2.2f", gTimeScale);
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("Camera Pos: %2.2f %2.2f %2.2f", mCamera.GetPos().x, mCamera.GetPos().y, mCamera.GetPos().z);
//		glTranslatef(0.0f, -1.0f, 0);
//		glPrint("Camera View: %2.2f %2.2f %2.2f", mCamera.GetView().x, mCamera.GetView().y, mCamera.GetView().z);
		
		glPopMatrix();	
	}  

	glFlush();
	
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

bool LoadData(bool camera, unsigned fileNum)
{

	std::string fileNumstr = std::to_string(fileNum);
	std::string fileName = "data" + fileNumstr + ".dat";
	std::ifstream dataFile(fileName, std::ios::in);	
	if ( !dataFile )
		return false;

	Vector3 cameraPos;
	Vector3 cameraAxic;
	float cameraAngle;
	//Vector3 cameraHeadPitchRoll;
	//Vector3 cameraUp;
	//Vector3 cameraView;
	//Quaternion cameraQ;

	dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z
		>> cameraAxic.x >> cameraAxic.y >> cameraAxic.z 
		>> cameraAngle;
				//>> cameraView.x >> cameraView.y >> cameraView.z		
				//>> cameraUp.x >> cameraUp.y >> cameraUp.z
				//>> cameraQ.x >> cameraQ.y >> cameraQ.z >> cameraQ.w;
				//>> cameraHeadPitchRoll.x >> cameraHeadPitchRoll.y >> cameraHeadPitchRoll.z;

	if (camera)
	{
		mCamera.SetPos(cameraPos);
		//mCamera.SetAngle(cameraAngle);		
		//mCamera.SetUp(cameraUp);

		Quaternion q;
		q.fromAxisAngle(cameraAxic, cameraAngle);
		q.normalize();
		mCamera.SetQuaternion(q);

		//mCamera.SetQuaternion(cameraPos, cameraView, cameraUp);
		//mCamera.SetQuaternionFromHeadPitchRoll(cameraHeadPitchRoll.x, cameraHeadPitchRoll.y, cameraHeadPitchRoll.z);
		//mCamera.SetView(cameraView);

		

		//mCamera.SetQuaternion(cameraPos, cameraPos2, cameraUp);
	}

	dataFile >> gLightAmbient[0] >> gLightAmbient[1] >> gLightAmbient[2] >> gLightAmbient[3];
	dataFile >> gLightDiffuse[0] >> gLightDiffuse[1] >> gLightDiffuse[2] >> gLightDiffuse[3];
	dataFile >> gLightPosition[0] >> gLightPosition[1] >> gLightPosition[2] >> gLightPosition[3];

	Vector3 graviAcc;

	dataFile >> graviAcc.x >> graviAcc.y >> graviAcc.z;
//	mGame.SetGraviAcc(graviAcc);

	unsigned int numEntities = 0;

	dataFile >> numEntities;

	mGame.SetNumEntities(numEntities);

	int numMass = 0;

	dataFile >>  numMass;

	//mGame.SetNumMasses(numMass);

	for(int i = 0; i < numMass; i++) {
		float m = 0.0f, r = 0.0f,
		posx = 0.0f, posy = 0.0f, posz = 0.0f, 
		velx = 0.0f, vely = 0.0f, velz = 0.0f;
		//bool isLight = false;
		Color4f color(0.0f, 0.0f, 0.0f, 0.0f);
		dataFile >> m >> r 
			>> posx >> posy >> posz 
			>> velx >> vely >> velz
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetMass(m, r, Vector3(posx, posy, posz), Vector3(velx, vely, velz), /*isLight,*/ color);        
	}

	int numBoxs = 0;
	dataFile >> numBoxs;

	//mGame.SetNumBoxes(numBoxs);
	for(int i = 0; i < numBoxs; i++) {
		float m = 0.0;
		Vector3 pos, size, vel, angle, angleVel;
		Color4f color;
		dataFile >> m 
			>> pos.x >> pos.y >> pos.z
			>> size.x >> size.y >> size.z
			>> vel.x >> vel.y >> vel.z
			>> angle.x >> angle.y >> angle.z
			>> angleVel.x >> angleVel.y >> angleVel.z
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetBox(m, pos, vel, size, angle, angleVel, color);
	}

	int numLines = 0;
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

	dataFile.close();
	return true;
}


void UpdateKeys()
{
	if (gKeys[VK_SPACE])
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}
	if (gKeys['L'] && !gLightOnKey)			// Клавиша 'L' нажата и не удерживается?
	{
		gLightOnKey=true;						// lp присвоили TRUE
		gLightOn=!gLightOn;				// Переключение света TRUE/FALSE
		if (!gLightOn)					// Если не свет
		{
			glDisable(GL_LIGHTING);		// Запрет освещения
		}
		else							// В противном случае
		{
			glEnable(GL_LIGHTING);		// Разрешить освещение
		}
	}
	if (!gKeys['L'])					// Клавиша 'L' Отжата?
	{
		gLightOnKey=false;						// Если так, то lp равно FALSE
	}

	if( gKeys[VK_F1] )				// Была ли нажата F1?
	{
		gKeys[VK_F1] = false;			// Если так, меняем значение ячейки массива на false
		KillGLWindow();					// Разрушаем текущее окно
		gFullscreen = !gFullscreen;		// Переключаем режим
		// Пересоздаём наше OpenGL окно
		if( !CreateGLWindow( ("NeHe OpenGL структура"), gWidth, gHeight, 32, gFullscreen ) )
		{
			//return 0;						// Выходим, если это невозможно
		}
	} 

	if( gKeys[VK_F5])
	{
		gKeys[VK_F5] = false;
		mGame.release();
		LoadData(true, SceneNum);
		//LoadData(false);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['1'])
	{
		gKeys['1'] = false;
		mGame.release();
		SceneNum = 1;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['2'])
	{
		gKeys['2']= false;
		mGame.release();
		SceneNum = 2;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['3'])
	{
		gKeys['3'] = false;
		mGame.release();
		SceneNum = 3;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['4'])
	{
		gKeys['4'] = false;
		mGame.release();
		SceneNum = 4;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['5'])
	{
		gKeys['5'] = false;
		mGame.release();
		SceneNum = 5;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['6'])
	{
		gKeys['6'] = false;
		mGame.release();
		SceneNum = 6;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys['7'])
	{
		gKeys['7'] = false;
		mGame.release();
		SceneNum = 7;
		LoadData(true, SceneNum);
		gTime = 0.0f;
		gTimeScale =1.0f;
		SetGLLight();
	}
	if( gKeys[VK_RIGHT])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateLR(1.0f*gAngleScale*gTimeScale);
		else
			mCamera.RotateLR(.1f*gAngleScale*gTimeScale);				
	}
	if( gKeys[VK_LEFT])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateLR(-1.0f*gAngleScale*gTimeScale);
			//mCamera.RotateLR(0.0f);
		else
			mCamera.RotateLR(-0.1f*gAngleScale*gTimeScale);
			//mCamera.RotateLR(0.0f);
	}
	if( gKeys[VK_UP])
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddAngleY(1.0f);
// 		else
// 			mCamera.AddAngleY(0.1f);


		if (gKeys[VK_SHIFT])
			mCamera.RotateUpDown(1.0f*gAngleScale*gTimeScale);
		else
			mCamera.RotateUpDown(0.1f*gAngleScale*gTimeScale);
	}
	if( gKeys[VK_DOWN])
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddAngleY(-1.0f);
// 		else
// 			mCamera.AddAngleY(-0.1f);

		if (gKeys[VK_SHIFT])
			mCamera.RotateUpDown(-1.0f*gAngleScale*gTimeScale);
		else
			mCamera.RotateUpDown(-0.1f*gAngleScale*gTimeScale);

	}
	if( gKeys['W'])
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddPosZ(1.0f);
// 		else
// 			mCamera.AddPosZ(0.1f);
		
		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(1.0f*gMoveScale*gTimeScale);
		else
			mCamera.MoveCamera(0.1f*gMoveScale*gTimeScale);
	}
	if( gKeys['S']) 
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddPosZ(-1.0f);
// 		else
// 			mCamera.AddPosZ(-0.1f);

		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(-1.0f*gMoveScale*gTimeScale);
		else
			mCamera.MoveCamera(-0.1f*gMoveScale*gTimeScale);
	}
	if( gKeys['A'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(-1.0f*gMoveScale*gTimeScale);
		else
			mCamera.MoveLRCamera(-0.1f*gMoveScale*gTimeScale);
	}
	if( gKeys['D'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(1.0f*gMoveScale*gTimeScale);
		else
			mCamera.MoveLRCamera(0.1f*gMoveScale*gTimeScale);
	}
	if (gKeys[VK_TAB] && !gShowDebugInfoKey)
	{
		gShowDebugInfoKey = true;
		gShowDebugInfo = !gShowDebugInfo;
	}
	if (!gKeys[VK_TAB])
		gShowDebugInfoKey = false;
	if (gKeys[VK_ADD])
		gTimeScale += 0.01f;
	if (gKeys[VK_SUBTRACT])
		gTimeScale -= 0.01f;
	if (gKeys['0'])
		gTimeScale = 1.0f;
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
			ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// Младшее слово=Width, старшее слово=Height
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
	MSG  msg;           // Структура для хранения сообщения Windows
	
	bool  done = false;	// Логическая переменная для выхода из цикла

	DWORD tickCount = 0;
	DWORD lastTickCount = 0;

	// Спрашивает пользователя, какой режим экрана он предпочитает
	//if( MessageBox( NULL, "Хотите ли Вы запустить приложение в полноэкранном режиме?",  "Запустить в полноэкранном режиме?", MB_YESNO | MB_ICONQUESTION) == IDNO )
	//{
		//fullscreen = false;          // Оконный режим
	//

	if (!LoadData(true, SceneNum)) {
		MessageBox (NULL, "Load Data Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 1;													// Return False (Failure)
	}

	// Создать наше OpenGL окно
	if( !CreateGLWindow( "NeHe OpenGL окно", gWidth, gHeight, 32, gFullscreen ) )
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
							fps = framesPerSecond;
							framesPerSecond = 0.0f;
						}
						lastTickCount = tickCount;			// Set Last Count To Current Count
						DrawGLScene();						// Рисуем сцену
						SwapBuffers( hDC );					// Меняем буфер (двойная буферизация)
					}

					if(gKeys[VK_ESCAPE])						// Было ли нажата клавиша ESC?
					{
						done = true;							// ESC говорит об останове выполнения программы
					}
					UpdateKeys();
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();						// Разрушаем окно
	return ( msg.wParam );              // Выходим из программы
}