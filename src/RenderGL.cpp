#include "RenderGL.h"

#include <string>

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>



//#include "Camera.h"

#include "Math/Quaternion.h"
#include "Math/Vector3.h"

HDC		hDC = nullptr;              // Приватный контекст устройства GDI
HGLRC	hRC	 = nullptr;              // Постоянный контекст рендеринга
HWND	hWnd = nullptr;              // Здесь будет хранится дескриптор окна
HINSTANCE  rhInstance = nullptr;              // Здесь будет хранится дескриптор приложения 

//GLfloat gLightAmbient[4];//= { 0.8f, 0.8f, 0.8f, 1.0f }; // Значения фонового света
//GLfloat gLightDiffuse[4];//= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
//GLfloat gLightPosition[4];//= { 3.0f, 3.0f, 4.0f, 1.0f };     // Позиция света

GLYPHMETRICSFLOAT gmFont[256];	// Storage For Information About Our Outline Font Characters
GLuint	gFontBase;				// Base Display List For The Font Set
//GLuint		texture[4];									// 3 Textures				 
//GLUquadricObj	*q;										// Quadratic For Drawing A Sphere
//WNDPROC *WndProc;					  // Процедура обработки сообщений					 


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


RenderGL::RenderGL()
{

}

RenderGL::~RenderGL()
{

}

void RenderGL::BuildFont()								// Build Our Bitmap Font
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

void RenderGL::KillFont()									// Delete The Font
{
	glDeleteLists(gFontBase, 256);								// Delete All 256 Characters
}

void RenderGL::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	float		length = 0;								// Used To Find The Length Of The Text
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	for (unsigned int loop = 0; loop<(strlen(text)); loop++)	// Loop To Find Text Length
	{
		length += gmFont[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}

	glPushMatrix();
	//glTranslatef(-length/2,0.0f,0.0f);					// Center Our Text On The Screen
	glPushAttrib(GL_ALL_ATTRIB_BITS);							// Pushes The Display List Bits
	glListBase(gFontBase);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
	glPopMatrix();
}

int RenderGL::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
	int Status = FALSE;									// Status Indicator

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

GLvoid RenderGL::ReSizeGLScene(unsigned width, unsigned height)        // Изменить размер и инициализировать окно GL
{
	if (height == 0)              // Предотвращение деления на ноль
	{
		height = 1;
	}

	glViewport(0, 0, width, height);          // Сброс текущей области вывода

	glMatrixMode(GL_PROJECTION);            // Выбор матрицы проекций
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

void RenderGL::SetGLLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, rLightAmbient);    // Установка Фонового Света
	glLightfv(GL_LIGHT0, GL_DIFFUSE, rLightDiffuse);    // Установка Диффузного Света
	glLightfv(GL_LIGHT0, GL_POSITION, rLightPosition);   // Позиция света
	glEnable(GL_LIGHT0); // Разрешение источника света номер один
	if (LightOn)
		glEnable(GL_LIGHTING);
}

bool RenderGL::CreateWin(long  WndProc, const char *title, unsigned width, unsigned height, int bits)
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

	rhInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
	wc.lpfnWndProc = WNDPROC(WndProc);					  // Процедура обработки сообщений
	wc.cbClsExtra = 0;									 // Нет дополнительной информации для окна
	wc.cbWndExtra = 0;							 	    // Нет дополнительной информации для окна
	wc.hInstance = rhInstance;						   // Устанавливаем дескриптор
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);       // Загружаем указатель мышки
	wc.hbrBackground = NULL;								// Фон не требуется для GL
	wc.lpszMenuName = NULL;							   // Меню в окне не будет
	wc.lpszClassName = "OpenGL";						  // Устанавливаем имя классу

	if (!RegisterClass(&wc))              // Пытаемся зарегистрировать класс окна
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Выход и возвращение функцией значения false
	}

	if (Fullscreen)                // Полноэкранный режим?
	{
		DEVMODE dmScreenSettings;            // Режим устройства
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // Очистка для хранения установок

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Размер структуры Devmode
		dmScreenSettings.dmPelsWidth = width;				// Ширина экрана
		dmScreenSettings.dmPelsHeight = height;			   // Высота экрана
		dmScreenSettings.dmBitsPerPel = bits;			  // Глубина цвета
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя

		// Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				Fullscreen = false;          // Выбор оконного режима (fullscreen = false)
			}
			else
			{
				// Выскакивающее окно, сообщающее пользователю о закрытие окна.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;            // Выход и возвращение функцией false
			}
		}
	}

	if (Fullscreen)                  // Мы остались в полноэкранном режиме?
	{
		dwExStyle = WS_EX_APPWINDOW;      // Расширенный стиль окна
		dwStyle = WS_POPUP;            // Обычный стиль окна
		ShowCursor(false);               // Скрыть указатель мышки
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;       // Расширенный стиль окна
		dwStyle = WS_OVERLAPPEDWINDOW;						// Обычный стиль окна
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры

	if (!(hWnd = CreateWindowEx(
		dwExStyle,										// Расширенный стиль для окна
		("OpenGL"),									   // Имя класса
		title,										  // Заголовок окна
		WS_CLIPSIBLINGS |							 // Требуемый стиль для окна
		WS_CLIPCHILDREN |							// Требуемый стиль для окна
		dwStyle,								   // Выбираемые стили для окна
		0, 0,									  // Позиция окна
		WindowRect.right - WindowRect.left,		 // Вычисление подходящей ширины
		WindowRect.bottom - WindowRect.top,		// Вычисление подходящей высоты
		NULL,								   // Нет родительского
		NULL,								  // Нет меню
		rhInstance,							 // Дескриптор приложения
		NULL)))							// Не передаём ничего до WM_CREATE (???)
	{
		Release();                // Восстановить экран
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	static  PIXELFORMATDESCRIPTOR pfd =              // pfd сообщает Windows каким будет вывод на экран каждого пикселя
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

	if (!(hDC = GetDC(hWnd)))              // Можем ли мы получить Контекст Устройства?
	{
		Release();                // Восстановить экран
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        // Найден ли подходящий формат пикселя?
	{
		Release();                // Восстановить экран
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?
	{
		Release();                // Восстановить экран
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	if (!(hRC = wglCreateContext(hDC))) // Возможно ли установить Контекст Рендеринга?
	{
		Release();                // Восстановить экран
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	if (!wglMakeCurrent(hDC, hRC))            // Попробовать активировать Контекст Рендеринга
	{
		Release();                // Восстановить экран
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	ShowWindow(hWnd, SW_SHOW);				  // Показать окно
	SetForegroundWindow(hWnd);				 // Слегка повысим приоритет
	SetFocus(hWnd);							// Установить фокус клавиатуры на наше окно
	ReSizeGLScene(width, height);			   // Настроим перспективу для нашего OpenGL экрана.

	if (!Init())                  // Инициализация только что созданного окна
	{
		Release();                // Восстановить экран
		MessageBox(NULL, ("Initialization Failed."), ("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	return true;                  // Всё в порядке!
}

void RenderGL::EnableLight()
{
	glEnable(GL_LIGHTING);		// Разрешить освещение
	LightOn = true;
}

void RenderGL::DisableLight()
{		
	glDisable(GL_LIGHTING);		// Запрет освещения
	LightOn = false;
}

void RenderGL::SetFullScreen(bool Fullscreen_)
{
	Fullscreen = Fullscreen_;
}

bool RenderGL::Init()
{
	//if (!LoadGLTextures())								// If Loading The Textures Failed
	//	{
	//		return FALSE;									// Return False
	//	}
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);

	SetGLLight();

	BuildFont();				// Build The Font

	//q = gluNewQuadric();								// Create A New Quadratic
	//gluQuadricNormals(q, GL_SMOOTH);					// Generate Smooth Normals For The Quad
	//gluQuadricTexture(q, GL_TRUE);						// Enable Texture Coords For The Quad

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping

	return true;                // Инициализация прошла успешно


}

bool RenderGL::Release()
{
	bool res = true;
	if (Fullscreen)              // Мы в полноэкранном режиме?
	{
		ChangeDisplaySettings(NULL, 0);        // Если да, то переключаемся обратно в оконный режим
		ShowCursor(true);            // Показать курсор мышки
	}
	if (hRC)                // Существует ли Контекст Рендеринга?
	{
		if (!wglMakeCurrent(NULL, NULL))        // Возможно ли освободить RC и DC?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);			
			res = false;
		}
		if (!wglDeleteContext(hRC))        // Возможно ли удалить RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);			
			res = false;
		}
		hRC = NULL;              // Установить RC в NULL
	}
	if (hDC && !ReleaseDC(hWnd, hDC))          // Возможно ли уничтожить DC?
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                // Установить DC в NULL		
		res = false;
	}
	if (hWnd && !DestroyWindow(hWnd))            // Возможно ли уничтожить окно?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                // Установить hWnd в NULL
		res = false;
	}
	if (!UnregisterClass("OpenGL", rhInstance))        // Возможно ли разрегистрировать класс
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		rhInstance = NULL;                // Установить hInstance в NULL
		res = false;
	}

	KillFont();

	return res;
}

void RenderGL::BeginDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // Очистить экран и буфер глубины	
	glMatrixMode(GL_MODELVIEW);								  // Выбор матрицы вида модели
	glLoadIdentity();										 // Сбросить текущую матрицу

	//gluLookAt(mCamera.GetPos().x, mCamera.GetPos().y, mCamera.GetPos().z, 
	//mCamera.GetView().x, mCamera.GetView().y, mCamera.GetView().z, 
	//mCamera.GetUp().x, mCamera.GetUp().y, mCamera.GetUp().z);

	Quaternion q = rCamera->GetQuaternion();
	Vector3 cameraAxic;
	float cameraAngle;
	q.toAxisAngle(cameraAxic, cameraAngle);
	glRotatef(cameraAngle, cameraAxic.x, cameraAxic.y, cameraAxic.z);

	Vector3 cameraPos = rCamera->GetPos();
	glTranslatef(cameraPos.x, cameraPos.y, cameraPos.z);


	SetGLLight();
}

void RenderGL::EndDraw()
{
	glFlush();
	SwapBuffers(hDC);					// Меняем буфер (двойная буферизация)
}

void RenderGL::DrawDebugInfo()
{
	glLoadIdentity();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5.0f, 3.6f, -10.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	glPrint("Scene #: %d", *rSceneNum);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("FPS: %2.2f", *rfps);						// Print GL Text To The Screen
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("UPS: %2.2f", *rups);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("Time: %2.2f", *rTime);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("Time Scale: %2.2f", *rTimeScale);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("Camera Pos: %2.2f %2.2f %2.2f", rCamera->GetPos().x, rCamera->GetPos().y, rCamera->GetPos().z);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("Camera View: %2.2f %2.2f %2.2f", rCamera->GetView().x, rCamera->GetView().y, rCamera->GetView().z);
	Quaternion q = rCamera->GetQuaternion();
	Vector3 axic;
	float angle;
	q.toAxisAngle(axic, angle);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("Camera Axic: %2.2f %2.2f %2.2f", axic.x, axic.y, axic.z);
	glTranslatef(0.0f, -1.0f, 0);
	glPrint("Camera Angle: %2.2f", angle);
	glPopMatrix();
}

void RenderGL::DrawBox(const Vector3& pos_, const Vector3& size, const Vector3& axic, const float angle, const Color4f& color) const
{
	glPushMatrix();

	glTranslatef(pos_.x, pos_.y, pos_.z);

	glRotatef(angle, axic.x, axic.y, axic.z);

	glColor3f(color.r, color.g, color.b);

	Vector3 pos;

	glBegin(GL_QUADS);       // Начало рисования четырехугольников
	// Передняя грань
	//glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
	glVertex3f(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 1 (Перед)
	glVertex3f(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 2 (Перед)
	glVertex3f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 3 (Перед)
	glVertex3f(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 4 (Перед)
	// Задняя грань
	//glNormal3f( 0.0f, 0.0f,-1.0f);     // Нормаль указывает от наблюдателя
	glVertex3f(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 1 (Зад)
	glVertex3f(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 2 (Зад)
	glVertex3f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 3 (Зад)
	glVertex3f(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 4 (Зад)
	// Верхняя грань
	// 		glNormal3f( 0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
	glVertex3f(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 4 (Верх)

	// Нижняя грань
	//glNormal3f( 0.0f,-1.0f, 0.0f);     // Нормаль указывает вниз
	glVertex3f(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 4 (Верх)
	// Правая грань
	//glNormal3f( 1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
	glVertex3f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 4 (Верх)
	// Левая грань
	//glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
	glVertex3f(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z + size.z / 2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.z / 2.0f); // Точка 4 (Верх)
	glEnd();

	glPopMatrix();
}

void RenderGL::DrawSphere(const Vector3& pos, const float r, const Color4f& color) const
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	gluQuadricTexture(quadratic, GL_FALSE);

	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);

	//glRotatef(-90.0f, 1, 0, 0);
	//glRotatef(rt, 0, 0, 1);
	//rt += 0.1f;
	//r += 0.001f;

	glColor3f(color.r, color.g, color.b);


	//glBindTexture(GL_TEXTURE_2D, GLuint(4));			// Select Texture 2 (1)
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping	

	gluSphere(quadratic, r, 32, 16);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	//glBindTexture(GL_TEXTURE_2D, GLuint(0));

	glPopMatrix();

	gluDeleteQuadric(quadratic);

}