#include "GEngine.h"
#include "RenderGL.h"

#include <cstdio>
#include <cstdarg>

#include <gl\GL.h>
#include <gl\GLU.h>

//#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "GLu32.lib")

HDC		hDC;              // ��������� �������� ���������� GDI
HGLRC	hRC;              // ���������� �������� ����������
HWND	hWnd;              // ����� ����� �������� ���������� ����
HINSTANCE  hInstance;              // ����� ����� �������� ���������� ���������� 

GLfloat gLightAmbient[4] = {0.25f, 0.25f, 0.25f, 1.0f};
GLfloat gLightDiffuse[4] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gLightPosition[4] = {0.25f, 0.25f, 0.25f, 1.0f};

GLYPHMETRICSFLOAT gmFont[256];	// Storage For Information About Our Outline Font Characters
GLuint	gFontBase;				// Base Display List For The Font Set

RenderGL::RenderGL(bool fullscreen_, bool light_, Vector3f cameraPos, Quaternion cameraQ)
: Render(fullscreen_, light_, cameraPos, cameraQ)
{
}


RenderGL::~RenderGL()
{
}

bool RenderGL::createWindow(const char* title, unsigned width, unsigned height, unsigned char bits)
{
	GLuint    PixelFormat;              // ������ ��������� ����� ������
	WNDCLASS  wc;                // ��������� ������ ����
	DWORD    dwExStyle;              // ����������� ����� ����
	DWORD    dwStyle;              // ������� ����� ����
	RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;              // ���������� ����� ������������ � 0
	WindowRect.right = (long)width;              // ���������� ������ ������������ � Width
	WindowRect.top = (long)0;                // ���������� ������� ������������ � 0
	WindowRect.bottom = (long)height;              // ���������� ������ ������������ � Height
	//fullscreen = fullscreenflag;              // ������������� �������� ���������� ���������� fullscreen
	hInstance = GetModuleHandle(NULL);        // ������� ���������� ������ ����������
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // ���������� ��� ����������� � ������ ������� DC
	wc.lpfnWndProc = (WNDPROC)WndProc;          // ��������� ��������� ���������
												//todo wc.lpfnWndProc =
	wc.cbClsExtra = 0;              // ��� �������������� ���������� ��� ����
	wc.cbWndExtra = 0;              // ��� �������������� ���������� ��� ����
	wc.hInstance = hInstance;            // ������������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // ��������� ������ �� ���������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // ��������� ��������� �����
	wc.hbrBackground = NULL;              // ��� �� ��������� ��� GL
	wc.lpszMenuName = NULL;              // ���� � ���� �� �����
	wc.lpszClassName = "OpenGL";            // ������������� ��� ������
	if (!RegisterClass(&wc))              // �������� ���������������� ����� ����
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ����� � ����������� �������� �������� false
	}
	if (fullscreen)                // ������������� �����?
	{
		DEVMODE dmScreenSettings;            // ����� ����������
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // ������� ��� �������� ���������
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // ������ ��������� Devmode
		dmScreenSettings.dmPelsWidth = width;        // ������ ������
		dmScreenSettings.dmPelsHeight = height;        // ������ ������
		dmScreenSettings.dmBitsPerPel = bits;        // ������� �����
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// ����� �������
																				 // �������� ���������� ��������� ����� � �������� ���������.  ����������: CDS_FULLSCREEN ������� ������ ����������.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// ���� ������������ � ������������� ����� ����������, ����� ���������� ��� ��������: ������� ����� ��� �����.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"GEngine GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;          // ����� �������� ������ (fullscreen = false)
			}
			else
			{
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;            // ����� � ����������� �������� false
			}
		}
	}
	if (fullscreen)                  // �� �������� � ������������� ������?
	{
		dwExStyle = WS_EX_APPWINDOW;          // ����������� ����� ����
		dwStyle = WS_POPUP;            // ������� ����� ����
		ShowCursor(false);              // ������ ��������� �����
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // ����������� ����� ����
		dwStyle = WS_OVERLAPPEDWINDOW;        // ������� ����� ����
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // ��������� ���� ���������� �������
	if (!(hWnd = CreateWindowEx(dwExStyle,          // ����������� ����� ��� ����
		"OpenGL",          // ��� ������
		title,            // ��������� ����
		WS_CLIPSIBLINGS |        // ��������� ����� ��� ����
		WS_CLIPCHILDREN |        // ��������� ����� ��� ����
		dwStyle,          // ���������� ����� ��� ����
		0, 0,            // ������� ����
		WindowRect.right - WindowRect.left,    // ���������� ���������� ������
		WindowRect.bottom - WindowRect.top,    // ���������� ���������� ������
		NULL,            // ��� �������������
		NULL,            // ��� ����
		hInstance,          // ���������� ����������
		NULL)))          // �� ������� ������ �� WM_CREATE (???)
	{
		killWindow();                // ������������ �����
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}
	static  PIXELFORMATDESCRIPTOR pfd =            // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
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
	if (!(hDC = GetDC(hWnd)))              // ����� �� �� �������� �������� ����������?
	{
		killWindow();                // ������������ �����
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        // ������ �� ���������� ������ �������?
	{
		killWindow();                // ������������ �����
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // �������� �� ���������� ������ �������?
	{
		killWindow();                // ������������ �����
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}
	if (!(hRC = wglCreateContext(hDC)))          // �������� �� ���������� �������� ����������?
	{
		killWindow();                // ������������ �����
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}
	if (!wglMakeCurrent(hDC, hRC))            // ����������� ������������ �������� ����������
	{
		killWindow();                // ������������ �����
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // ������� false
	}
	ShowWindow(hWnd, SW_SHOW);              // �������� ����
	SetForegroundWindow(hWnd);              // ������ ������� ���������
	SetFocus(hWnd);                // ���������� ����� ���������� �� ���� ����
	resize(width, height);              // �������� ����������� ��� ������ OpenGL ������.
	init();

	//if (!init())                  // ������������� ������ ��� ���������� ����
	//{
		//killWindow();                // ������������ �����
		//MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		//return false;                // ������� false
	//}

	return true;
}

void RenderGL::killWindow()
{
	if (fullscreen)              // �� � ������������� ������?
	{
		ChangeDisplaySettings(NULL, 0);        // ���� ��, �� ������������� ������� � ������� �����
		ShowCursor(true);            // �������� ������ �����
	}

	if (hRC)                // ���������� �� �������� ����������?
	{
		if (!wglMakeCurrent(NULL, NULL))        // �������� �� ���������� RC � DC?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))        // �������� �� ������� RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;              // ���������� RC � NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))          // �������� �� ���������� DC?
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                // ���������� DC � NULL
	}

	if (hWnd && !DestroyWindow(hWnd))            // �������� �� ���������� ����?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                // ���������� hWnd � NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))        // �������� �� ����������������� �����
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                // ���������� hInstance � NULL
	}

	killFont();
}

void RenderGL::init()
{
	glShadeModel(GL_SMOOTH);            // ��������� ������� �������� �����������
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // ������� ������ � ������ ����
	glClearDepth(1.0f);              // ��������� ������� ������ �������
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glDepthFunc(GL_LEQUAL);            // ��� ����� �������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // ��������� � ���������� �����������
	//glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate i

	setLight();
	glEnable(GL_COLOR_MATERIAL);	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_TEXTURE_2D);	

	buildFont();				// Build The Font
}

void RenderGL::resize(unsigned width, unsigned height)
{
	if (height == 0)
	{
		height = 1;              // �������������� ������� �� ����
	}

	glViewport(0, 0, width, height);          // ����� ������� ������� ������

	glMatrixMode(GL_PROJECTION);            // ����� ������� ��������
	glLoadIdentity();              // ����� ������� ��������

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);	// ���������� ����������� �������������� �������� ��� ����

	glMatrixMode(GL_MODELVIEW);            // ����� ������� ���� ������
	glLoadIdentity();              // ����� ������� ���� ������
}

void RenderGL::setLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, gLightAmbient);    // ��������� �������� �����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gLightDiffuse);    // ��������� ���������� �����
														//glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);   // ������� �����

	glEnable(GL_LIGHT0); // ���������� ��������� ����� ����� ����

	if (lightOn)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}

void RenderGL::beginDraw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // �������� ����� � ����� �������	
	glMatrixMode(GL_MODELVIEW);								  // ����� ������� ���� ������
	glLoadIdentity();										 // �������� ������� �������
	glTranslatef(-camera.pos.x, -camera.pos.y, -camera.pos.z);
	Vector3f axic;
	float angle;
	camera.q.toAngleAxis(angle, axic);
	glRotatef(angle, axic.x, -axic.y, axic.z);	
}

void RenderGL::endDraw() const
{
	//glFlush();
	SwapBuffers(hDC);//_WIN32					// ������ ����� (������� �����������)
}

void RenderGL::buildFont()
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
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
											//"Comic Sans MS"				// Font Name
		"Arial"							// Font Name
	);

	SelectObject(hDC, font);							// Selects The Font We Created

	wglUseFontOutlines(hDC,							// Select The Current DC
		0,								// Starting Character
		255,							// Number Of Display Lists To Build
		gFontBase,							// Starting Display Lists
		0.0f,							// Deviation From The True Outlines
		0.1f,							// Font Thickness In The Z Direction
		WGL_FONT_POLYGONS,			// Use Polygons, Not Lines
									//WGL_FONT_LINES,					// Use Polygons, Not Lines
		gmFont);							// Address Of Buffer To Recieve Data

}

void RenderGL::killFont()
{
	glDeleteLists(gFontBase, 256);								// Delete All 256 Characters
}

void RenderGL::print(const Vector3f &pos, const char *fmt, ...)
{
	float		length = 0;								// Used To Find The Length Of The Text
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	for (unsigned loop = 0; loop<(strlen(text)); loop++)	// Loop To Find Text Length
	{
		length += gmFont[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}

	glLoadIdentity();

	//glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);					// Center Our Text On The Screen
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(gFontBase);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
	//glPopMatrix();
}

void RenderGL::drawTriangleStrip(size_t n, const Vector3f * vertexs, const Vector3f * normals, const Color4f & color) const
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (size_t i = 0; i < n; ++i)
	{
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
	}
	glEnd;
}

void RenderGL::drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const
{
	glNormal3f(n.x, n.y, n.z);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLES);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
	glEnd();
}

void RenderGL::drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const
{
	glNormal3f(n.x, n.y, n.z);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
		glVertex3f(d.x, d.y, d.z);
	glEnd();
}

void RenderGL::drawQuad(const Vector3f & a, const Vector3f & b, const Vector3f & c, const Vector3f & d)
{
	Vector3f n = Vector3f(b - a) * Vector3f(c - a);
	n.unitize();
	glNormal3f(n.x, n.y, n.z);
	glBegin(GL_QUADS);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glVertex3f(d.x, d.y, d.z);
	glEnd();
}

void RenderGL::drawQuad(const Vector3f * vertexs, const Vector3f & n, const Color4f & colors)
{
	glNormal3f(n.x, n.y, n.z);
	glBegin(GL_QUADS);
	glColor4f(colors.r, colors.g, colors.b, colors.a);
	glVertex3f(vertexs[0].x, vertexs[0].y, vertexs[0].z);
	glVertex3f(vertexs[1].x, vertexs[1].y, vertexs[1].z);
	glVertex3f(vertexs[2].x, vertexs[2].y, vertexs[2].z);
	glVertex3f(vertexs[3].x, vertexs[3].y, vertexs[3].z);
	glEnd();

}


void RenderGL::drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	Vector3f ad = Vector3f(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f bd = Vector3f(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f cd = Vector3f(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f dd = Vector3f(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f au = Vector3f(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
	Vector3f bu = Vector3f(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f cu = Vector3f(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f du = Vector3f(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

	//drawQuad(ad, bd, cd, cd, color);
	//drawQuad(cd, cu, du, dd, color);
	//drawQuad(dd, du, au, ad, color);
	//drawQuad(ad, au, bu, bd, color);
	//drawQuad(bd, bu, cu, cd, color);
	//drawQuad(cu, bu, au, du, color);

	glPopMatrix();
}

void RenderGL::drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axic, const Color4f& color) const
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(angle, axic.x, axic.y, axic.z);
	Vector3f ad = Vector3f(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f bd = Vector3f(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f cd = Vector3f(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f dd = Vector3f(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f au = Vector3f(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
	Vector3f bu = Vector3f(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f cu = Vector3f(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f du = Vector3f(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

	//drawQuad(ad, bd, cd, cd, color);
	//drawQuad(cd, cu, du, dd, color);
	//drawQuad(dd, du, au, ad, color);
	//drawQuad(ad, au, bu, bd, color);
	//drawQuad(bd, bu, cu, cd, color);
	//drawQuad(au, bu, cu, du, color);

	glPopMatrix();
}

void RenderGL::drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	Vector3f axic;
	float angle;
	rotation.toAngleAxis(angle, axic);
	glRotatef(angle, axic.x, axic.y, axic.z);
	Vector3f ad = Vector3f(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f bd = Vector3f(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f cd = Vector3f(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f dd = Vector3f(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f au = Vector3f(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
	Vector3f bu = Vector3f(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f cu = Vector3f(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f du = Vector3f(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

	//drawQuad(ad, bd, cd, cd, color);
	//drawQuad(cd, cu, du, dd, color);
	//drawQuad(dd, du, au, ad, color);
	//drawQuad(ad, au, bu, bd, color);
	//drawQuad(bd, bu, cu, cd, color);
	//drawQuad(cu, bu, au, du, color);

	glPopMatrix();
}

void RenderGL::drawSphere(const Vector3f & pos, const float r, const Color4f & color) const
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	gluQuadricTexture(quadratic, GLU_FALSE);

	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glColor4f(color.r, color.g, color.b, color.a);


	//glBindTexture(GL_TEXTURE_2D, GLuint(4));			// Select Texture 2 (1)
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping	

	gluSphere(quadratic, r, 16, 16);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	//glBindTexture(GL_TEXTURE_2D, GLuint(0));

	glPopMatrix();

	gluDeleteQuadric(quadratic);
}
