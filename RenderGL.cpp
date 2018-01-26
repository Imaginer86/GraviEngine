#include "GEngine.h"
#include "RenderGL.h"

#include <cstdio>
#include <cstdarg>

#include <gl\GL.h>
#include <gl\GLU.h>

//#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "GLu32.lib")

HDC		hDC;              // Приватный контекст устройства GDI
HGLRC	hRC;              // Постоянный контекст рендеринга
HWND	hWnd;              // Здесь будет хранится дескриптор окна
HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения 

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
	GLuint    PixelFormat;              // Хранит результат после поиска
	WNDCLASS  wc;                // Структура класса окна
	DWORD    dwExStyle;              // Расширенный стиль окна
	DWORD    dwStyle;              // Обычный стиль окна
	RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;              // Установить левую составляющую в 0
	WindowRect.right = (long)width;              // Установить правую составляющую в Width
	WindowRect.top = (long)0;                // Установить верхнюю составляющую в 0
	WindowRect.bottom = (long)height;              // Установить нижнюю составляющую в Height
	//fullscreen = fullscreenflag;              // Устанавливаем значение глобальной переменной fullscreen
	hInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
	wc.lpfnWndProc = (WNDPROC)WndProc;          // Процедура обработки сообщений
												//todo wc.lpfnWndProc =
	wc.cbClsExtra = 0;              // Нет дополнительной информации для окна
	wc.cbWndExtra = 0;              // Нет дополнительной информации для окна
	wc.hInstance = hInstance;            // Устанавливаем дескриптор
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // Загружаем указатель мышки
	wc.hbrBackground = NULL;              // Фон не требуется для GL
	wc.lpszMenuName = NULL;              // Меню в окне не будет
	wc.lpszClassName = "OpenGL";            // Устанавливаем имя классу
	if (!RegisterClass(&wc))              // Пытаемся зарегистрировать класс окна
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Выход и возвращение функцией значения false
	}
	if (fullscreen)                // Полноэкранный режим?
	{
		DEVMODE dmScreenSettings;            // Режим устройства
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // Очистка для хранения установок
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Размер структуры Devmode
		dmScreenSettings.dmPelsWidth = width;        // Ширина экрана
		dmScreenSettings.dmPelsHeight = height;        // Высота экрана
		dmScreenSettings.dmBitsPerPel = bits;        // Глубина цвета
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя
																				 // Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"GEngine GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;          // Выбор оконного режима (fullscreen = false)
			}
			else
			{
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;            // Выход и возвращение функцией false
			}
		}
	}
	if (fullscreen)                  // Мы остались в полноэкранном режиме?
	{
		dwExStyle = WS_EX_APPWINDOW;          // Расширенный стиль окна
		dwStyle = WS_POPUP;            // Обычный стиль окна
		ShowCursor(false);              // Скрыть указатель мышки
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // Расширенный стиль окна
		dwStyle = WS_OVERLAPPEDWINDOW;        // Обычный стиль окна
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры
	if (!(hWnd = CreateWindowEx(dwExStyle,          // Расширенный стиль для окна
		"OpenGL",          // Имя класса
		title,            // Заголовок окна
		WS_CLIPSIBLINGS |        // Требуемый стиль для окна
		WS_CLIPCHILDREN |        // Требуемый стиль для окна
		dwStyle,          // Выбираемые стили для окна
		0, 0,            // Позиция окна
		WindowRect.right - WindowRect.left,    // Вычисление подходящей ширины
		WindowRect.bottom - WindowRect.top,    // Вычисление подходящей высоты
		NULL,            // Нет родительского
		NULL,            // Нет меню
		hInstance,          // Дескриптор приложения
		NULL)))          // Не передаём ничего до WM_CREATE (???)
	{
		killWindow();                // Восстановить экран
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	static  PIXELFORMATDESCRIPTOR pfd =            // pfd сообщает Windows каким будет вывод на экран каждого пикселя
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // Размер дескриптора данного формата пикселей
		1,                  // Номер версии
		PFD_DRAW_TO_WINDOW |              // Формат для Окна
		PFD_SUPPORT_OPENGL |              // Формат для OpenGL
		PFD_DOUBLEBUFFER,              // Формат для двойного буфера
		PFD_TYPE_RGBA,                // Требуется RGBA формат
		bits,                  // Выбирается бит глубины цвета
		0, 0, 0, 0, 0, 0,              // Игнорирование цветовых битов
		0,                  // Нет буфера прозрачности
		0,                  // Сдвиговый бит игнорируется
		0,                  // Нет буфера накопления
		0, 0, 0, 0,                // Биты накопления игнорируются
		32,                  // 32 битный Z-буфер (буфер глубины)
		0,                  // Нет буфера трафарета
		0,                  // Нет вспомогательных буферов
		PFD_MAIN_PLANE,                // Главный слой рисования
		0,                  // Зарезервировано
		0, 0, 0                  // Маски слоя игнорируются
	};
	if (!(hDC = GetDC(hWnd)))              // Можем ли мы получить Контекст Устройства?
	{
		killWindow();                // Восстановить экран
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        // Найден ли подходящий формат пикселя?
	{
		killWindow();                // Восстановить экран
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?
	{
		killWindow();                // Восстановить экран
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!(hRC = wglCreateContext(hDC)))          // Возможно ли установить Контекст Рендеринга?
	{
		killWindow();                // Восстановить экран
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!wglMakeCurrent(hDC, hRC))            // Попробовать активировать Контекст Рендеринга
	{
		killWindow();                // Восстановить экран
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	ShowWindow(hWnd, SW_SHOW);              // Показать окно
	SetForegroundWindow(hWnd);              // Слегка повысим приоритет
	SetFocus(hWnd);                // Установить фокус клавиатуры на наше окно
	resize(width, height);              // Настроим перспективу для нашего OpenGL экрана.
	init();

	//if (!init())                  // Инициализация только что созданного окна
	//{
		//killWindow();                // Восстановить экран
		//MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		//return false;                // Вернуть false
	//}

	return true;
}

void RenderGL::killWindow()
{
	if (fullscreen)              // Мы в полноэкранном режиме?
	{
		ChangeDisplaySettings(NULL, 0);        // Если да, то переключаемся обратно в оконный режим
		ShowCursor(true);            // Показать курсор мышки
	}

	if (hRC)                // Существует ли Контекст Рендеринга?
	{
		if (!wglMakeCurrent(NULL, NULL))        // Возможно ли освободить RC и DC?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))        // Возможно ли удалить RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;              // Установить RC в NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))          // Возможно ли уничтожить DC?
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                // Установить DC в NULL
	}

	if (hWnd && !DestroyWindow(hWnd))            // Возможно ли уничтожить окно?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                // Установить hWnd в NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))        // Возможно ли разрегистрировать класс
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                // Установить hInstance в NULL
	}

	killFont();
}

void RenderGL::init()
{
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы
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
		height = 1;              // Предотвращение деления на ноль
	}

	glViewport(0, 0, width, height);          // Сброс текущей области вывода

	glMatrixMode(GL_PROJECTION);            // Выбор матрицы проекций
	glLoadIdentity();              // Сброс матрицы проекции

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);	// Вычисление соотношения геометрических размеров для окна

	glMatrixMode(GL_MODELVIEW);            // Выбор матрицы вида модели
	glLoadIdentity();              // Сброс матрицы вида модели
}

void RenderGL::setLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, gLightAmbient);    // Установка Фонового Света
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gLightDiffuse);    // Установка Диффузного Света
														//glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);   // Позиция света

	glEnable(GL_LIGHT0); // Разрешение источника света номер один

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // Очистить экран и буфер глубины	
	glMatrixMode(GL_MODELVIEW);								  // Выбор матрицы вида модели
	glLoadIdentity();										 // Сбросить текущую матрицу
	glTranslatef(-camera.pos.x, -camera.pos.y, -camera.pos.z);
	Vector3f axic;
	float angle;
	camera.q.toAngleAxis(angle, axic);
	glRotatef(angle, axic.x, -axic.y, axic.z);	
}

void RenderGL::endDraw() const
{
	//glFlush();
	SwapBuffers(hDC);//_WIN32					// Меняем буфер (двойная буферизация)
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
