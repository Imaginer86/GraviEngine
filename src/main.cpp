#include <Windows.h>

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glaux.h>

#include "Game.h"

#include <fstream>

HGLRC	hRC	 = NULL;              // ���������� �������� ����������
HDC		hDC  = NULL;              // ��������� �������� ���������� GDI
HWND	hWnd = NULL;              // ����� ����� �������� ���������� ����
HINSTANCE  hInstance;              // ����� ����� �������� ���������� ���������� 

bool  keys[256];                // ������, ������������ ��� �������� � �����������
bool  active = true;                // ���� ���������� ����, ������������� � true �� ���������
bool  fullscreen = true;              // ���� ������ ����, ������������� � ������������� �� ���������

bool light;      // ���� ��� / ����
bool lp;         // L ������?

Game mGame;

GLUquadricObj *quadratic;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; // �������� �������� �����
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; // �������� ���������� �����
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };     // ������� �����

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
	//gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 10.0, 400.0);

	glMatrixMode( GL_MODELVIEW );            // ����� ������� ���� ������

	glTranslatef(0.0f, 0.0f, -60.0f);
	//glLoadIdentity();              // ����� ������� ���� ������
}

int InitGL( GLvoid )                // ��� ��������� ������� OpenGL ���������� �����
{
	glShadeModel( GL_SMOOTH );            // ��������� ������� �������� �����������
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // ������� ������ � ������ ����
	glClearDepth( 1.0f );              // ��������� ������� ������ �������
	glEnable( GL_DEPTH_TEST );            // ��������� ���� �������
	glDepthFunc( GL_LEQUAL );            // ��� ����� �������
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );      // ��������� � ���������� �����������
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // ��������� �������� �����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // ��������� ���������� �����
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // ������� �����
	glEnable(GL_LIGHT1); // ���������� ��������� ����� ����� ����
	return true;                // ������������� ������ �������
}

int DrawGLScene( GLvoid )                // ����� ����� ����������� ��� ����������
{
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );      // �������� ����� � ����� �������
	//glLoadIdentity();              // �������� ������� �������
	//return true;                // ���������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	GLenum light = GL_LIGHT0;
	for(int i = 0; i < mGame.numOfMasses; i++) {
		glPushMatrix();
		glTranslatef(mGame.masses[i].pos.x, mGame.masses[i].pos.y, mGame.masses[i].pos.z);

// 		if (mGame.masses[i].isLight) {
// 			glDisable(GL_LIGHTING);
// 			GLfloat massLight[] = {mGame.masses[i].color.r, mGame.masses[i].color.g,mGame.masses[i].color.b,mGame.masses[i].color.a,};
// 			GLfloat massPos[] = {mGame.masses[i].pos.x, mGame.masses[i].pos.y, mGame.masses[i].pos.z, 1.0f};
// 			glLightfv(light ,GL_DIFFUSE, massLight);
// 			glLightfv(light ,GL_POSITION, massPos);            
// 			glEnable(light);
// 			light++;
// 		}              

		glColor3f(mGame.masses[i].color.r, mGame.masses[i].color.g, mGame.masses[i].color.b);
		gluSphere(quadratic, mGame.masses[i].r, 32,32);

// 		if (mGame.masses[i].isLight)
// 			glEnable(GL_LIGHTING);

		glPopMatrix();
	}

	return true;
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

BOOL LoadData() {

	std::ifstream dataFile("data.dat", std::ios::in);	
	if ( !dataFile )
		return FALSE;

	float timeScale = 0.0f, distanceScale = 0.0f, gravi = 0.0f, radiusEarth = 0.0f;
	int numMass = 0;

	dataFile >>  numMass;

	mGame.SetSize(numMass);

	for (int i = 0; i < numMass; i++) {
		float m = 0.0f, r =0.0f,
			posx = 0.0f, posy = 0.0f, posz = 0.0f, 
			velx = 0.0f, vely = 0.0f, velz = 0.0f;
		bool isLight = false;
		Color4f color = {0.0f, 0.0f, 0.0f, 0.0f};
		dataFile >> m >> r 
			>> posx >> posy >> posz 
			>> velx >> vely >> velz
			//>> isLight
			>> color.r >> color.g >> color.b >> color.a;
		mGame.SetMass(i, m, r, Vector3D(posx, posy, posz), Vector3D(velx, vely, velz), /*isLight,*/ color);        
	}

	dataFile.close();
	return TRUE;
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
	BOOL  done = false;            // ���������� ���������� ��� ������ �� �����

	DWORD tickCount = 0;
	DWORD lastTickCount = 0;

	// ���������� ������������, ����� ����� ������ �� ������������
	if( MessageBox( NULL, "������ �� �� ��������� ���������� � ������������� ������?",  "��������� � ������������� ������?", MB_YESNO | MB_ICONQUESTION) == IDNO )
	{
		fullscreen = false;          // ������� �����
	}
	// ������� ���� OpenGL ����
	if( !CreateGLWindow( "NeHe OpenGL ����", 1024, 768, 32, fullscreen ) )
	{
		return 0;              // �����, ���� ���� �� ����� ���� �������
	}

	if (!LoadData()) {
		MessageBox (NULL, "Load Data Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;													// Return False (Failure)
	}

	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)


	lastTickCount = GetTickCount ();							// Get Tick Count

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
				if(keys[VK_ESCAPE])        // ���� �� ������ ������� ESC?
				{
					done = true;      // ESC ������� �� �������� ���������� ���������
				}
				else            // �� ����� ��� ������, ������� �����.
				{
					tickCount = GetTickCount();				// Get The Tick Count						
					mGame.Update(float (tickCount - lastTickCount)/1000.0f );
					lastTickCount = tickCount;			// Set Last Count To Current Count
					DrawGLScene();        // ������ �����
					SwapBuffers( hDC );    // ������ ����� (������� �����������)
					if (keys['L'] && !lp) // ������� 'L' ������ � �� ������������?
					{
						lp=TRUE;      // lp ��������� TRUE
						light=!light; // ������������ ����� TRUE/FALSE
						if (!light)               // ���� �� ����
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
						lp=FALSE;      // ���� ���, �� lp ����� FALSE
					}

				}
			}
			if( keys[VK_F1] )          // ���� �� ������ F1?
			{
				keys[VK_F1] = false;        // ���� ���, ������ �������� ������ ������� �� false
				KillGLWindow();          // ��������� ������� ����
				fullscreen = !fullscreen;      // ����������� �����
				// ���������� ���� OpenGL ����
				if( !CreateGLWindow( ("NeHe OpenGL ���������"), 1024, 768, 32, fullscreen ) )
				{
					return 0;        // �������, ���� ��� ����������
				}
			}
		}
	}
	// Shutdown
	KillGLWindow();                // ��������� ����
	return ( msg.wParam );              // ������� �� ���������
}

