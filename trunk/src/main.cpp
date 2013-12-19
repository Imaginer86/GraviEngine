//#include <Windows.h>
#include <fstream>
//#include <gl\GL.h>
//#include <gl\GLU.h>
#include "gl\glaux.h"

#include "Game.h"
#include "Camera.h"
#include "Color.h"

HGLRC	hRC	 = NULL;              // ���������� �������� ����������
HDC		hDC  = NULL;              // ��������� �������� ���������� GDI
HWND	hWnd = NULL;              // ����� ����� �������� ���������� ����
HINSTANCE  hInstance;              // ����� ����� �������� ���������� ���������� 

bool  keys[256];                // ������, ������������ ��� �������� � �����������
bool  active = true;                // ���� ���������� ����, ������������� � true �� ���������
bool  fullscreen = false;              // ���� ������ ����, ������������� � ������������� �� ���������
bool  pause = true;

bool LightOn = true;      // ���� ��� / ����
bool lp = false;         // L ������?

bool showDebugInfo = true;
bool ld = false;

Game mGame;
Camera mCamera;

float timeScale = 1.0f;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; // �������� �������� �����
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; // �������� ���������� �����
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };     // ������� �����

float fps = 0.0f;
float ups = 0.0f;

GLYPHMETRICSFLOAT gmf[256];	// Storage For Information About Our Outline Font Characters
GLuint	base;				// Base Display List For The Font Set

GLvoid BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID

	base = glGenLists(256);								// Storage For 256 Characters

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
		base,							// Starting Display Lists
		0.0f,							// Deviation From The True Outlines
		0.1f,							// Font Thickness In The Z Direction
		WGL_FONT_POLYGONS,			// Use Polygons, Not Lines
		//WGL_FONT_LINES,					// Use Polygons, Not Lines
		gmf);							// Address Of Buffer To Recieve Data
}

GLvoid KillFont(GLvoid)									// Delete The Font
{
	glDeleteLists(base, 256);								// Delete All 256 Characters
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
		length+=gmf[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}

	glTranslatef(-length/2,0.0f,0.0f);					// Center Our Text On The Screen

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
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
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);    // ��������� �������� �����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);    // ��������� ���������� �����
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);   // ������� �����
	glEnable(GL_LIGHT0); // ���������� ��������� ����� ����� ����
	if (LightOn)
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

//	SetLight();

	

	BuildFont();										// Build The Font

	return true;                // ������������� ������ �������
}


GLvoid KillGLWindow( GLvoid )              // ���������� ���������� ����
{
	if( fullscreen )              // �� � ������������� ������?
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
	GLuint    PixelFormat;              // ������ ��������� ����� ������
	WNDCLASS  wc;                // ��������� ������ ����
	DWORD    dwExStyle;              // ����������� ����� ����
	DWORD    dwStyle;              // ������� ����� ����

	RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;              // ���������� ����� ������������ � 0
	WindowRect.right=(long)width;              // ���������� ������ ������������ � Width
	WindowRect.top=(long)0;                // ���������� ������� ������������ � 0
	WindowRect.bottom=(long)height;              // ���������� ������ ������������ � Height

	fullscreen=fullscreenflag;              // ������������� �������� ���������� ���������� fullscreen

	hInstance    = GetModuleHandle(NULL);        // ������� ���������� ������ ����������
	wc.style    = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // ���������� ��� ����������� � ������ ������� DC
	wc.lpfnWndProc    = (WNDPROC) WndProc;          // ��������� ��������� ���������
	wc.cbClsExtra    = 0;              // ��� �������������� ���������� ��� ����
	wc.cbWndExtra    = 0;              // ��� �������������� ���������� ��� ����
	wc.hInstance    = hInstance;            // ������������� ����������
	wc.hIcon    = LoadIcon(NULL, IDI_WINLOGO);        // ��������� ������ �� ���������
	wc.hCursor    = LoadCursor(NULL, IDC_ARROW);        // ��������� ��������� �����
	wc.hbrBackground  = NULL;              // ��� �� ��������� ��� GL
	wc.lpszMenuName    = NULL;              // ���� � ���� �� �����
	wc.lpszClassName  = "OpenGL";            // ������������� ��� ������

	if( !RegisterClass( &wc ) )              // �������� ���������������� ����� ����
	{
		MessageBox( NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ����� � ����������� �������� �������� false
	}

	if( fullscreen )                // ������������� �����?
	{
		DEVMODE dmScreenSettings;            // ����� ����������
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );    // ������� ��� �������� ���������
		dmScreenSettings.dmSize=sizeof( dmScreenSettings );      // ������ ��������� Devmode
		dmScreenSettings.dmPelsWidth  =   width;        // ������ ������
		dmScreenSettings.dmPelsHeight  =   height;        // ������ ������
		dmScreenSettings.dmBitsPerPel  =   bits;        // ������� �����
		dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// ����� �������

		// �������� ���������� ��������� ����� � �������� ���������.  ����������: CDS_FULLSCREEN ������� ������ ����������.
		if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// ���� ������������ � ������������� ����� ����������, ����� ���������� ��� ��������: ������� ����� ��� �����.
			if( MessageBox( NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES )
			{
				fullscreen = false;          // ����� �������� ������ (fullscreen = false)
			}
			else
			{
				// ������������� ����, ���������� ������������ � �������� ����.
				MessageBox( NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP );
				return false;            // ����� � ����������� �������� false
			}
		}
	}
	if(fullscreen)                  // �� �������� � ������������� ������?
	{
		dwExStyle  =   WS_EX_APPWINDOW;          // ����������� ����� ����
		dwStyle    =   WS_POPUP;            // ������� ����� ����
		ShowCursor( false );              // ������ ��������� �����
	}
	else
	{
		dwExStyle  =   WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // ����������� ����� ����
		dwStyle    =   WS_OVERLAPPEDWINDOW;        // ������� ����� ����
	}

	AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );      // ��������� ���� ���������� �������

	if( !( hWnd = CreateWindowEx(  dwExStyle,          // ����������� ����� ��� ����
		("OpenGL"),          // ��� ������
		title,            // ��������� ����
		WS_CLIPSIBLINGS |        // ��������� ����� ��� ����
		WS_CLIPCHILDREN |        // ��������� ����� ��� ����
		dwStyle,          // ���������� ����� ��� ����
		0, 0,            // ������� ����
		WindowRect.right-WindowRect.left,    // ���������� ���������� ������
		WindowRect.bottom-WindowRect.top,    // ���������� ���������� ������
		NULL,            // ��� �������������
		NULL,            // ��� ����
		hInstance,          // ���������� ����������
		NULL ) ) )          // �� ������� ������ �� WM_CREATE (???)
	{
		KillGLWindow();                // ������������ �����
		MessageBox( NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                // ������� false
	}

	static  PIXELFORMATDESCRIPTOR pfd=            // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // ������ ����������� ������� ������� ��������
		1,                  // ����� ������
		PFD_DRAW_TO_WINDOW |              // ������ ��� ����
		PFD_SUPPORT_OPENGL |              // ������ ��� OpenGL
		PFD_DOUBLEBUFFER,              // ������ ��� �������� ������
		PFD_TYPE_RGBA,                // ��������� RGBA ������
		bits,                  // ���������� ��� ������� �����
		0, 0, 0, 0, 0, 0,              // ������������� �������� �����
		0,                  // ��� ������ ������������
		0,                  // ��������� ��� ������������
		0,                  // ��� ������ ����������
		0, 0, 0, 0,                // ���� ���������� ������������
		32,                  // 32 ������ Z-����� (����� �������)
		0,                  // ��� ������ ���������
		0,                  // ��� ��������������� �������
		PFD_MAIN_PLANE,                // ������� ���� ���������
		0,                  // ���������������
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

	ShowWindow( hWnd, SW_SHOW );              // �������� ����
	SetForegroundWindow( hWnd );              // ������ ������� ���������
	SetFocus( hWnd );                // ���������� ����� ���������� �� ���� ����
	ReSizeGLScene( width, height );              // �������� ����������� ��� ������ OpenGL ������.

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
	glMatrixMode(GL_MODELVIEW);								// ����� ������� ���� ������
	glLoadIdentity();              // �������� ������� �������

	gluLookAt(mCamera.GetPos().x, mCamera.GetPos().y, mCamera.GetPos().z, 
		mCamera.GetPos2().x, mCamera.GetPos2().y, mCamera.GetPos2().z, 
		0, 1, 0);

	SetLight();

	mGame.Draw();

	if (showDebugInfo)
	{
		//glLoadIdentity();
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(mCamera.GetPos().x+4.5f, mCamera.GetPos().y+3.5f, mCamera.GetPos().z+10);
		glRotatef(180, 0, 1, 0);
		glScalef(0.2f, 0.2f, 0.2f);
		glPrint("FPS: %2.2f", fps);						// Print GL Text To The Screen
		glPopMatrix();
		glPushMatrix();
		glTranslatef(mCamera.GetPos().x+4.5f, mCamera.GetPos().y+3.3f, mCamera.GetPos().z+10);
		glRotatef(180, 0, 1, 0);
		glScalef(0.2f, 0.2f, 0.2f);
		glPrint("UPS: %2.2f", ups);						// Print GL Text To The Screen
		glPopMatrix();
		glPushMatrix();
		glTranslatef(mCamera.GetPos().x+4.5f, mCamera.GetPos().y+3.1f, mCamera.GetPos().z+10);
		glRotatef(180, 0, 1, 0);
		glScalef(0.2f, 0.2f, 0.2f);
		glPrint("Time Scale: %2.2f", timeScale);						// Print GL Text To The Screen
		glPopMatrix();
	}  
	
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
	mCamera.SetPos2(cameraPos2);
	//mCamera.SetAngle(cameraAngle);

	dataFile >> LightAmbient[0] >> LightAmbient[1] >> LightAmbient[2] >> LightAmbient[3];
	dataFile >> LightDiffuse[0] >> LightDiffuse[1] >> LightDiffuse[2] >> LightDiffuse[3];
	dataFile >> LightPosition[0] >> LightPosition[1] >> LightPosition[2] >> LightPosition[3];

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
	if (keys[VK_SPACE]) {
		pause = !pause;
		keys[VK_SPACE] = false;
	}
	if (keys['L'] && !lp) // ������� 'L' ������ � �� ������������?
	{
		lp=true;      // lp ��������� TRUE
		LightOn=!LightOn; // ������������ ����� TRUE/FALSE
		if (!LightOn)               // ���� �� ����
		{
			glDisable(GL_LIGHTING);  // ������ ���������
		}
		else                      // � ��������� ������
		{
			glEnable(GL_LIGHTING);   // ��������� ���������
		}
	}
	if (!keys['L']) // ������� 'L' ������?
	{
		lp=false;      // ���� ���, �� lp ����� FALSE
	}

	if( keys[VK_F1] )          // ���� �� ������ F1?
	{
		keys[VK_F1] = false;        // ���� ���, ������ �������� ������ ������� �� false
		KillGLWindow();          // ��������� ������� ����
		fullscreen = !fullscreen;      // ����������� �����
		// ���������� ���� OpenGL ����
		if( !CreateGLWindow( ("NeHe OpenGL ���������"), 1024, 768, 32, fullscreen ) )
		{
			//return 0;        // �������, ���� ��� ����������
		}
	} 
	if( keys[VK_F5])
	{
		keys[VK_F5] = false;
		mGame.release();
		LoadData();
		SetLight();
	}
	if( keys[VK_RIGHT]) {
		if (keys[VK_SHIFT])
			mCamera.AddAngleX(1.0f);
		else
			mCamera.AddAngleX(0.1f);				
	}
	if( keys[VK_LEFT]) {
		if (keys[VK_SHIFT])
			mCamera.AddAngleX(-1.0f);
		else
			mCamera.AddAngleX(-0.1f);
	}
	if( keys[VK_UP]) {
		if (keys[VK_SHIFT])
			mCamera.AddAngleY(1.0f);
		else
			mCamera.AddAngleY(0.1f);
	}
	if( keys[VK_DOWN]) {
		if (keys[VK_SHIFT])
			mCamera.AddAngleY(-1.0f);
		else
			mCamera.AddAngleY(-0.1f);
	}
	if( keys['W']) {
		if (keys[VK_SHIFT])
			mCamera.AddPosZ(1.0f);
		else
			mCamera.AddPosZ(0.1f);
	}
	if( keys['S']) {
		if (keys[VK_SHIFT])
			mCamera.AddPosZ(-1.0f);
		else
			mCamera.AddPosZ(-0.1f);
	}
	if( keys['A']) {
		if (keys[VK_SHIFT])
			mCamera.AddPosX(1.0f);
		else
			mCamera.AddPosX(0.1f);
	}
	if( keys['D']) {
		if (keys[VK_SHIFT])
			mCamera.AddPosX(-1.0f);
		else
			mCamera.AddPosX(-0.1f);
	}
	if (keys[VK_TAB] && !ld)
	{
		ld = true;
		showDebugInfo = !showDebugInfo;
	}
	if (!keys[VK_TAB])
		ld = false;
	if (keys[VK_ADD])
		timeScale += 0.01f;
	if (keys[VK_SUBTRACT])
		timeScale -= 0.01f;
	if (keys['0'])
		timeScale = 1.0f;
}

LRESULT CALLBACK WndProc(  HWND  hWnd,            // ���������� ������� ����
						 UINT  uMsg,            // ��������� ��� ����� ����
						 WPARAM  wParam,            // �������������� ����������
						 LPARAM  lParam)            // �������������� ����������
{
	switch (uMsg)                // �������� ��������� ��� ����
	{
	case WM_ACTIVATE:            // �������� ��������� ���������� ����
		{
			if( !HIWORD( wParam ) )          // ��������� ��������� �����������
			{
				active = true;          // ��������� �������
			}
			else
			{
				active = false;          // ��������� ������ �� �������
			}

			return 0;            // ������������ � ���� ��������� ���������
		}
	case WM_SYSCOMMAND:            // ������������� ��������� �������
		{
			switch ( wParam )            // ������������� ��������� �����
			{
			case SC_SCREENSAVE:        // �������� �� ���������� �����������?
			case SC_MONITORPOWER:        // �������� �� ������� ������� � ����� ���������� �������?
				return 0;          // ������������� ���
			}
			break;              // �����
		}
	case WM_CLOSE:              // �� �������� ��������� � ��������?
		{
			PostQuitMessage( 0 );          // ��������� ��������� � ������
			return 0;            // ��������� �����
		}

	case WM_KEYDOWN:            // ���� �� ������ ������?
		{
			keys[wParam] = true;          // ���� ���, �� ����������� ���� ������ true
			return 0;            // ������������
		}
	case WM_KEYUP:              // ���� �� �������� �������?
		{
			keys[wParam] = false;          //  ���� ���, �� ����������� ���� ������ false
			return 0;            // ������������
		}
	case WM_SIZE:              // �������� ������� OpenGL ����
		{
			ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );  // ������� �����=Width, ������� �����=Height
			return 0;            // ������������
		}
	}
	// ���������� ��� �������������� ��������� DefWindowProc
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


int WINAPI WinMain(  HINSTANCE  hInstance,        // ���������� ����������
				   HINSTANCE  hPrevInstance,        // ���������� ������������� ����������
				   LPSTR    lpCmdLine,        // ��������� ��������� ������
				   int    nCmdShow )        // ��������� ����������� ����
{
	MSG  msg;              // ��������� ��� �������� ��������� Windows
	bool  done = false;            // ���������� ���������� ��� ������ �� �����

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
	if( !CreateGLWindow( "NeHe OpenGL ����", 1024, 768, 32, fullscreen ) )
	{
		return 0;              // �����, ���� ���� �� ����� ���� �������
	}




	lastTickCount = GetTickCount ();							// Get Tick Count
	static float framesPerSecond = 0.0f	;
	static float lastTime = 0.0f;

	while( !done )                // ���� ������������, ���� done �� ����� true
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )    // ���� �� � ������� �����-������ ���������?
		{
			if( msg.message == WM_QUIT )        // �� ������� ��������� � ������?
			{
				done = true;          // ���� ���, done=true
			}
			else              // ���� ���, ������������ ���������
			{
				TranslateMessage( &msg );        // ��������� ���������
				DispatchMessage( &msg );        // �������� ���������
			}
		}
		else                // ���� ��� ���������
		{
			// ������������� �����.
			if( active )          // ������� �� ���������?
			{
				//else            // �� ����� ��� ������, ������� �����.
				{
					//--------------------------------
					{
						tickCount = GetTickCount();				// Get The Tick Count
						if (!pause) {						
							mGame.Update(timeScale*float(tickCount - lastTickCount)/1000.0f );
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
						DrawGLScene();        // ������ �����
						SwapBuffers( hDC );    // ������ ����� (������� �����������)
					}

					if(keys[VK_ESCAPE])        // ���� �� ������ ������� ESC?
					{
						done = true;      // ESC ������� �� �������� ���������� ���������
					}
					UpdateKeys();
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();                // ��������� ����
	return ( msg.wParam );              // ������� �� ���������
}