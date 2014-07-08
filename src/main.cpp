#pragma once
#include <fstream>
#include "GL\glaux.h"
#include "Game.h"
#include "Camera.h"
#include "Color.h"

bool  gFullscreen = false;              // ���� ������ ����, ������������� � ������������� �� ���������

int gWidth = 800;
int gHeight = 600;

HGLRC	hRC	 = NULL;              // ���������� �������� ����������
HDC		hDC  = NULL;              // ��������� �������� ���������� GDI
HWND	hWnd = NULL;              // ����� ����� �������� ���������� ����
HINSTANCE  hInstance;              // ����� ����� �������� ���������� ���������� 

bool  gKeys[256];                // ������, ������������ ��� �������� � �����������
bool  gActive = true;                // ���� ���������� ����, ������������� � true �� ���������

bool  gPause = true;

bool gLightOn = true;      // ���� ��� / ����
bool gLightOnKey = false;         // L ������?

bool gShowDebugInfo = true;
bool gShowDebugInfoKey = false;

Game mGame;
Camera mCamera;

float gTimeScale = 1.0f;

GLfloat gLightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; // �������� �������� �����
GLfloat gLightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; // �������� ���������� �����
GLfloat gLightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };     // ������� �����

float fps = 0.0f;
float ups = 0.0f;

GLYPHMETRICSFLOAT gmFont[256];	// Storage For Information About Our Outline Font Characters
GLuint	gFontBase;				// Base Display List For The Font Set

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
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(gFontBase);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
	glPopMatrix();
}

LRESULT  CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );        // �������� ������� WndProc


GLvoid ReSizeGLScene( GLsizei width, GLsizei height )        // �������� ������ � ���������������� ���� GL
{
	if( height == 0 )              // �������������� ������� �� ����
	{
		height = 1;
	}

	glViewport( 0, 0, width, height );          // ����� ������� ������� ������

	glMatrixMode( GL_PROJECTION );            // ����� ������� ��������
	glLoadIdentity();              // ����� ������� ��������

	// ���������� ����������� �������������� �������� ��� ����
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 10.0, 400.0);

// 	glMatrixMode( GL_MODELVIEW );            // ����� ������� ���� ������
// 	gluLookAt(mCamera.pos.x, mCamera.pos.y, mCamera.pos.z, 
// 		mCamera.pos.x, mCamera.pos.y, mCamera.pos.z + 50, 
// 		0, 100, 0);
// 
// 	//glTranslatef(0.0f, 0.0f, -60.0f);
// 	glLoadIdentity();              // ����� ������� ���� ������
}

void SetLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, gLightAmbient);    // ��������� �������� �����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gLightDiffuse);    // ��������� ���������� �����
	glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);   // ������� �����
	glEnable(GL_LIGHT0); // ���������� ��������� ����� ����� ����
	if (gLightOn)
		glEnable(GL_LIGHTING);
}


int InitGL( GLvoid )                // ��� ��������� ������� OpenGL ���������� �����
{
	glShadeModel( GL_SMOOTH );            // ��������� ������� �������� �����������
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // ������� ������ � ������ ����
	glClearDepth( 1.0f );              // ��������� ������� ������ �������
	glEnable( GL_DEPTH_TEST );            // ��������� ���� �������
	glDepthFunc( GL_LEQUAL );            // ��� ����� �������
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );      // ��������� � ���������� �����������
	glEnable(GL_COLOR_MATERIAL);

	SetLight();	

	BuildFont();				// Build The Font

	return true;                // ������������� ������ �������
}


GLvoid KillGLWindow( GLvoid )              // ���������� ���������� ����
{
	if( gFullscreen )              // �� � ������������� ������?
	{
		ChangeDisplaySettings( NULL, 0 );        // ���� ��, �� ������������� ������� � ������� �����
		ShowCursor( true );            // �������� ������ �����
	}
	if( hRC )                // ���������� �� �������� ����������?
	{
		if( !wglMakeCurrent( NULL, NULL ) )        // �������� �� ���������� RC � DC?
		{
			MessageBox( NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		if( !wglDeleteContext( hRC ) )        // �������� �� ������� RC?
		{
			MessageBox( NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		hRC = NULL;              // ���������� RC � NULL
	}
	if( hDC && !ReleaseDC( hWnd, hDC ) )          // �������� �� ���������� DC?
	{
		MessageBox( NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hDC=NULL;                // ���������� DC � NULL
	}
	if(hWnd && !DestroyWindow(hWnd))            // �������� �� ���������� ����?
	{
		MessageBox( NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hWnd = NULL;                // ���������� hWnd � NULL
	}
	if( !UnregisterClass( "OpenGL", hInstance ) )        // �������� �� ����������������� �����
	{
		MessageBox( NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                // ���������� hInstance � NULL
	}

	KillFont();
}


BOOL CreateGLWindow( LPCSTR title, int width, int height, int bits, bool fullscreenflag )
{
	GLuint		PixelFormat;			    // ������ ��������� ����� ������
	WNDCLASS	wc;						   // ��������� ������ ����
	DWORD		dwExStyle;				  // ����������� ����� ����
	DWORD		dwStyle;				 // ������� ����� ����

	RECT WindowRect;                       // Grabs Rectangle Upper Left / Lower Right Values

	WindowRect.left = 0L;					    	  // ���������� ����� ������������ � 0
	WindowRect.right = long(width);                  // ���������� ������ ������������ � Width
	WindowRect.top = 0L;					    	// ���������� ������� ������������ � 0
	WindowRect.bottom = long(height);              // ���������� ������ ������������ � Height

	gFullscreen = fullscreenflag;              // ������������� �������� ���������� ���������� fullscreen

	hInstance = GetModuleHandle(NULL);        // ������� ���������� ������ ����������

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // ���������� ��� ����������� � ������ ������� DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;					  // ��������� ��������� ���������
	wc.cbClsExtra		= 0;									 // ��� �������������� ���������� ��� ����
	wc.cbWndExtra		= 0;							 	    // ��� �������������� ���������� ��� ����
	wc.hInstance		= hInstance;						   // ������������� ����������
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);        // ��������� ������ �� ���������
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);       // ��������� ��������� �����
	wc.hbrBackground	= NULL;								// ��� �� ��������� ��� GL
	wc.lpszMenuName		= NULL;							   // ���� � ���� �� �����
	wc.lpszClassName	= "OpenGL";						  // ������������� ��� ������

	if( !RegisterClass( &wc ) )              // �������� ���������������� ����� ����
	{
		MessageBox( NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ����� � ����������� �������� �������� false
	}

	if( gFullscreen )                // ������������� �����?
	{
		DEVMODE dmScreenSettings;            // ����� ����������
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );    // ������� ��� �������� ���������

		dmScreenSettings.dmSize=sizeof( dmScreenSettings );      // ������ ��������� Devmode
		dmScreenSettings.dmPelsWidth  =   width;				// ������ ������
		dmScreenSettings.dmPelsHeight  =   height;			   // ������ ������
		dmScreenSettings.dmBitsPerPel  =   bits;			  // ������� �����
		dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// ����� �������

		// �������� ���������� ��������� ����� � �������� ���������.  ����������: CDS_FULLSCREEN ������� ������ ����������.
		if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// ���� ������������ � ������������� ����� ����������, ����� ���������� ��� ��������: ������� ����� ��� �����.
			if( MessageBox( NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES )
			{
				gFullscreen = false;          // ����� �������� ������ (fullscreen = false)
			}
			else
			{
				// ������������� ����, ���������� ������������ � �������� ����.
				MessageBox( NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP );
				return false;            // ����� � ����������� �������� false
			}
		}
	}

	if(gFullscreen)                  // �� �������� � ������������� ������?
	{
		dwExStyle  =   WS_EX_APPWINDOW;      // ����������� ����� ����
		dwStyle    =   WS_POPUP;            // ������� ����� ����
		ShowCursor( false );               // ������ ��������� �����
	}
	else
	{
		dwExStyle  =   WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;       // ����������� ����� ����
		dwStyle    =   WS_OVERLAPPEDWINDOW;						// ������� ����� ����
	}

	AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );      // ��������� ���� ���������� �������

	if( !( hWnd = CreateWindowEx(  
		dwExStyle,										// ����������� ����� ��� ����
		("OpenGL"),									   // ��� ������
		title,										  // ��������� ����
		WS_CLIPSIBLINGS |							 // ��������� ����� ��� ����
		WS_CLIPCHILDREN |							// ��������� ����� ��� ����
		dwStyle,								   // ���������� ����� ��� ����
		0, 0,									  // ������� ����
		WindowRect.right-WindowRect.left,		 // ���������� ���������� ������
		WindowRect.bottom-WindowRect.top,		// ���������� ���������� ������
		NULL,								   // ��� �������������
		NULL,								  // ��� ����
		hInstance,							 // ���������� ����������
		NULL ) ) )							// �� ������� ������ �� WM_CREATE (???)
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	static  PIXELFORMATDESCRIPTOR pfd=              // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // ������ ����������� ������� ������� ��������
		1,										 // ����� ������
		PFD_DRAW_TO_WINDOW |					// ������ ��� ����
		PFD_SUPPORT_OPENGL |				   // ������ ��� OpenGL
		PFD_DOUBLEBUFFER,					  // ������ ��� �������� ������
		PFD_TYPE_RGBA,						 // ��������� RGBA ������
		bits,								// ���������� ��� ������� �����
		0, 0, 0, 0, 0, 0,				   // ������������� �������� �����
		0,								  // ��� ������ ������������
		0,								 // ��������� ��� ������������
		0,								// ��� ������ ����������
		0, 0, 0, 0,					   // ���� ���������� ������������
		32,							  // 32 ������ Z-����� (����� �������)
		0,							 // ��� ������ ���������
		0,							// ��� ��������������� �������
		PFD_MAIN_PLANE,            // ������� ���� ���������
		0,						  // ���������������
		0, 0, 0                  // ����� ���� ������������
	};

	if( !( hDC = GetDC( hWnd ) ) )              // ����� �� �� �������� �������� ����������?
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	if( !( PixelFormat = ChoosePixelFormat( hDC, &pfd ) ) )        // ������ �� ���������� ������ �������?
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	if( !SetPixelFormat( hDC, PixelFormat, &pfd ) )          // �������� �� ���������� ������ �������?
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	if( !( hRC = wglCreateContext( hDC ) ) )          // �������� �� ���������� �������� ����������?
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}

	if( !wglMakeCurrent( hDC, hRC ) )            // ����������� ������������ �������� ����������
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	ShowWindow( hWnd, SW_SHOW );				  // �������� ����
	SetForegroundWindow( hWnd );				 // ������ ������� ���������
	SetFocus( hWnd );							// ���������� ����� ���������� �� ���� ����
	ReSizeGLScene( width, height );			   // �������� ����������� ��� ������ OpenGL ������.

	if( !InitGL() )                  // ������������� ������ ��� ���������� ����
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, ("Initialization Failed."), ("ERROR"), MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	return true;                  // �� � �������!
}


bool DrawGLScene()                // ����� ����� ����������� ��� ����������
{	  
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );      // �������� ����� � ����� �������	
	glMatrixMode(GL_MODELVIEW);								  // ����� ������� ���� ������
	glLoadIdentity();										 // �������� ������� �������

	gluLookAt(mCamera.GetPos().x, mCamera.GetPos().y, mCamera.GetPos().z, 
		mCamera.GetView().x, mCamera.GetView().y, mCamera.GetView().z, 
		0, 1, 0);

	SetLight();

	mGame.Draw();

	if (gShowDebugInfo)
	{
		glLoadIdentity();
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(-5.0f, 3.6f, -10.0f);	
		glScalef(0.2f, 0.2f, 0.2f);
		glPrint("FPS: %2.2f", fps);						// Print GL Text To The Screen
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("UPS: %2.2f", ups);
		glTranslatef(0.0f, -1.0f, 0);
		glPrint("Time Scale: %2.2f", gTimeScale);
		
		glPopMatrix();	}  
	
	return true;

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

BOOL LoadData() {
	std::ifstream dataFile("data.dat", std::ios::in);	
	if ( !dataFile )
		return FALSE;

	Vector3 cameraPos, cameraPos2, cameraAngle;

	dataFile >> cameraPos.x >> cameraPos.y >> cameraPos.z
			>> cameraPos2.x >> cameraPos2.y >> cameraPos2.z;
		//>> cameraAngle.x >> cameraAngle.y >> cameraAngle.z;
	mCamera.SetPos(cameraPos);
	mCamera.SetView(cameraPos2);
	//mCamera.SetAngle(cameraAngle);

	dataFile >> gLightAmbient[0] >> gLightAmbient[1] >> gLightAmbient[2] >> gLightAmbient[3];
	dataFile >> gLightDiffuse[0] >> gLightDiffuse[1] >> gLightDiffuse[2] >> gLightDiffuse[3];
	dataFile >> gLightPosition[0] >> gLightPosition[1] >> gLightPosition[2] >> gLightPosition[3];

	Vector3 graviAcc;

	dataFile >> graviAcc.x >> graviAcc.y >> graviAcc.z;
	mGame.SetGraviAcc(graviAcc);

	int numMass = 0;

	dataFile >>  numMass;

	mGame.SetNumMasses(numMass);

	for(int i = 0; i < numMass; i++) {
		float m = 0.0f, r = 0.0f,
		posx = 0.0f, posy = 0.0f, posz = 0.0f, 
		velx = 0.0f, vely = 0.0f, velz = 0.0f;
		//bool isLight = false;
		Color4f color = {0.0f, 0.0f, 0.0f, 0.0f};
		dataFile >> m >> r 
			>> posx >> posy >> posz 
			>> velx >> vely >> velz
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetMass(i, m, r, Vector3(posx, posy, posz), Vector3(velx, vely, velz), /*isLight,*/ color);        
	}

	int numBoxs = 0;
	dataFile >> numBoxs;

	mGame.SetNumBoxes(numBoxs);
	for(int i = 0; i < numBoxs; i++) {
		float m = 0.0;
		Vector3 pos, size, angle;
		Color4f color;
		dataFile >> m 
			>> pos.x >> pos.y >> pos.z
			>> size.x >> size.y >> size.z
			>> angle.x >> angle.y >> angle.z
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetBox(i, m, pos, size, angle, color);
	}

	int numLines = 0;
	dataFile >> numLines;
	mGame.SetNumLines(numLines);
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
		mGame.SetLine(i, m, r, h, pos, q, color);
	}

	dataFile.close();
	return TRUE;
}


void UpdateKeys()
{
	if (gKeys[VK_SPACE])
	{
		gPause = !gPause;
		gKeys[VK_SPACE] = false;
	}
	if (gKeys['L'] && !gLightOnKey)			// ������� 'L' ������ � �� ������������?
	{
		gLightOnKey=true;						// lp ��������� TRUE
		gLightOn=!gLightOn;				// ������������ ����� TRUE/FALSE
		if (!gLightOn)					// ���� �� ����
		{
			glDisable(GL_LIGHTING);		// ������ ���������
		}
		else							// � ��������� ������
		{
			glEnable(GL_LIGHTING);		// ��������� ���������
		}
	}
	if (!gKeys['L'])					// ������� 'L' ������?
	{
		gLightOnKey=false;						// ���� ���, �� lp ����� FALSE
	}

	if( gKeys[VK_F1] )				// ���� �� ������ F1?
	{
		gKeys[VK_F1] = false;			// ���� ���, ������ �������� ������ ������� �� false
		KillGLWindow();					// ��������� ������� ����
		gFullscreen = !gFullscreen;		// ����������� �����
		// ���������� ���� OpenGL ����
		if( !CreateGLWindow( ("NeHe OpenGL ���������"), gWidth, gHeight, 32, gFullscreen ) )
		{
			//return 0;						// �������, ���� ��� ����������
		}
	} 
	if( gKeys[VK_F5])
	{
		gKeys[VK_F5] = false;
		mGame.release();
		LoadData();
		SetLight();
	}
	if( gKeys[VK_RIGHT])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateView(1.0f*0.1f);
		else
			mCamera.RotateView(0.1f*0.1f);				
	}
	if( gKeys[VK_LEFT])
	{
		if (gKeys[VK_SHIFT])
			mCamera.RotateView(-1.0f*0.1f);
		else
			mCamera.RotateView(-0.1f*0.1f);
	}
	if( gKeys[VK_UP])
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddAngleY(1.0f);
// 		else
// 			mCamera.AddAngleY(0.1f);


		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(1.0f);
		else
			mCamera.MoveCamera(0.1f);
	}
	if( gKeys[VK_DOWN])
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddAngleY(-1.0f);
// 		else
// 			mCamera.AddAngleY(-0.1f);

		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(-1.0f);
		else
			mCamera.MoveCamera(-0.1f);

	}
	if( gKeys['W'])
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddPosZ(1.0f);
// 		else
// 			mCamera.AddPosZ(0.1f);

		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(1.0f);
		else
			mCamera.MoveCamera(0.1f);
	}
	if( gKeys['S']) 
	{
// 		if (gKeys[VK_SHIFT])
// 			mCamera.AddPosZ(-1.0f);
// 		else
// 			mCamera.AddPosZ(-0.1f);

		if (gKeys[VK_SHIFT])
			mCamera.MoveCamera(-1.0f);
		else
			mCamera.MoveCamera(-0.1f);
	}
	if( gKeys['A'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(-1.0f);
		else
			mCamera.MoveLRCamera(-0.1f);
	}
	if( gKeys['D'])
	{
		if (gKeys[VK_SHIFT])
			mCamera.MoveLRCamera(1.0f);
		else
			mCamera.MoveLRCamera(0.1f);
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

LRESULT CALLBACK WndProc(  HWND  hWnd,				// ���������� ������� ����
						 UINT  uMsg,				// ��������� ��� ����� ����
						 WPARAM  wParam,            // �������������� ����������
						 LPARAM  lParam)            // �������������� ����������
{
	switch (uMsg)                // �������� ��������� ��� ����
	{
	case WM_ACTIVATE:            // �������� ��������� ���������� ����
		{
			if( !HIWORD( wParam ) )          // ��������� ��������� �����������
			{
				gActive = true;					// ��������� �������
			}
			else
			{
				gActive = false;					// ��������� ������ �� �������
			}

			return 0;						// ������������ � ���� ��������� ���������
		}
	case WM_SYSCOMMAND:            // ������������� ��������� �������
		{
			switch ( wParam )            // ������������� ��������� �����
			{
			case SC_SCREENSAVE:				// �������� �� ���������� �����������?
			case SC_MONITORPOWER:			// �������� �� ������� ������� � ����� ���������� �������?
				return 0;						// ������������� ���
			}
			break;              // �����
		}
	case WM_CLOSE:              // �� �������� ��������� � ��������?
		{
			PostQuitMessage( 0 );			// ��������� ��������� � ������
			return 0;							// ��������� �����
		}

	case WM_KEYDOWN:            // ���� �� ������ ������?
		{
			gKeys[wParam] = true;			// ���� ���, �� ����������� ���� ������ true
			return 0;							// ������������
		}
	case WM_KEYUP:              // ���� �� �������� �������?
		{
			gKeys[wParam] = false;			//  ���� ���, �� ����������� ���� ������ false
			return 0;						// ������������
		}
	case WM_SIZE:              // �������� ������� OpenGL ����
		{
			ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// ������� �����=Width, ������� �����=Height
			return 0;											// ������������
		}
	}
	// ���������� ��� �������������� ��������� DefWindowProc
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


int WINAPI WinMain(	HINSTANCE  hInstance,				// ���������� ����������
					HINSTANCE  hPrevInstance,			// ���������� ������������� ����������
					LPSTR    lpCmdLine,					// ��������� ��������� ������
					int    nCmdShow )					// ��������� ����������� ����
{
	MSG  msg;           // ��������� ��� �������� ��������� Windows
	bool  done = false;	// ���������� ���������� ��� ������ �� �����

	DWORD tickCount = 0;
	DWORD lastTickCount = 0;

	// ���������� ������������, ����� ����� ������ �� ������������
	//if( MessageBox( NULL, "������ �� �� ��������� ���������� � ������������� ������?",  "��������� � ������������� ������?", MB_YESNO | MB_ICONQUESTION) == IDNO )
	//{
		//fullscreen = false;          // ������� �����
	//

	if (!LoadData()) {
		MessageBox (NULL, "Load Data Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;													// Return False (Failure)
	}

	// ������� ���� OpenGL ����
	if( !CreateGLWindow( "NeHe OpenGL ����", gWidth, gHeight, 32, gFullscreen ) )
	{
		return 0;              // �����, ���� ���� �� ����� ���� �������
	}

	lastTickCount = GetTickCount ();		// Get Tick Count
	static float framesPerSecond = 0.0f	;
	static float lastTime = 0.0f;

	while( !done )							// ���� ������������, ���� done �� ����� true
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )    // ���� �� � ������� �����-������ ���������?
		{
			if( msg.message == WM_QUIT )						// �� ������� ��������� � ������?
			{
				done = true;										// ���� ���, done=true
			}
			else												// ���� ���, ������������ ���������
			{
				TranslateMessage( &msg );							// ��������� ���������
				DispatchMessage( &msg );							// �������� ���������
			}
		}
		else	// ���� ��� ���������
		{
				// ������������� �����.
			if( gActive )          // ������� �� ���������?
			{
				//else            // �� ����� ��� ������, ������� �����.
				{
					//--------------------------------
					{
						tickCount = GetTickCount();				// Get The Tick Count
						if (!gPause) {						
							mGame.Update(gTimeScale*float(tickCount - lastTickCount)/1000.0f );
						} 					
						framesPerSecond++;
						float currentTime = tickCount*0.001f;
						if ((currentTime - lastTime) > 1.0f)
						{
							lastTime = currentTime;
							fps = framesPerSecond;
							framesPerSecond = 0.0f;
						}
						lastTickCount = tickCount;			// Set Last Count To Current Count
						DrawGLScene();						// ������ �����
						SwapBuffers( hDC );					// ������ ����� (������� �����������)
					}

					if(gKeys[VK_ESCAPE])						// ���� �� ������ ������� ESC?
					{
						done = true;							// ESC ������� �� �������� ���������� ���������
					}
					UpdateKeys();
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();						// ��������� ����
	return ( msg.wParam );              // ������� �� ���������
}