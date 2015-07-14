#pragma once

#include <windows.h>								// Header File For Windows
#include <GL\gl.h>
#include <GL\glu.h>
#include <vfw.h>



class Video
{
public:

	typedef struct {									// Structure For Keyboard Stuff
		bool *keyDown;								// Holds TRUE / FALSE For Each Key
	} Keys;												// Keys

	typedef struct {									// Contains Information Vital To Applications
		HINSTANCE		hInstance;						// Application Instance
		const char*		className;						// Application ClassName
	} Application;										// Application

	typedef struct {									// Window Creation Info
		Application*		application;				// Application Structure
		char*				title;						// Window Title
		int					width;						// Width
		int					height;						// Height
		int					bitsPerPixel;				// Bits Per Pixel
		BOOL				isFullScreen;				// FullScreen?
	} GL_WindowInit;									// GL_WindowInit

	/*
	typedef struct {									// Contains Information Vital To A Window
	Keys*				keys;						// Key Structure
	HWND				hWnd;						// Window Handle
	HDC					hDC;						// Device Context
	HGLRC				hRC;						// Rendering Context
	GL_WindowInit		init;						// Window Init
	BOOL				isVisible;					// Window Visible?
	DWORD				lastTickCount;				// Tick Counter
	} GL_Window;										// GL_Window
	*/

	//void TerminateApplication(GL_Window* window);		// Terminate The Application

	//void ToggleFullscreen(GL_Window* window);			// Toggle Fullscreen / Windowed Mode

	// These Are The Function You Must Provide
	bool Initialize();	// Performs All Your Initialization

	void Deinitialize(void);							// Performs All Your DeInitialization

	void Update(DWORD milliseconds);					// Perform Motion Updates

	void Draw(void);									// Perform All Your Scene Drawing
private:
	void flipIt(void* buffer); // Функция меняющая красный и синий цвет
	void OpenAVI(LPCSTR szFile);  // Вскрытие AVI файла (szFile)
	void GrabAVIFrame(int frame); // Захват кадра
	void CloseAVI();             // Функция закрытия

	// Пользовательские переменные
	float  angle;              // Для вращения
	int    next;               // Для анимации
	int    frame = 0;            // Счётчик кадров
	int    effect = 3;             // Текущий эффект
	bool   sp;                 // Пробел нажат?
	bool   env = true;           // Показ среды(По умолчанию включен)
	bool   ep;                 // 'E' нажато?
	bool   bg = true;            // Фон(по умолчанию включен)
	bool   bp;                 // 'B' нажато?


	
	PAVISTREAM       pavi;      // Дескриптор для открытия потока
	PGETFRAME        pgf;       // Указатель на объект GetFrame
	BITMAPINFOHEADER bmih;      // Заголовочная информация для DrawDibDraw декодирования
	long             lastframe; // Последний кадр анимации
	int              width;     // Ширина видео
	int              height;    // Высота видео
	char             *pdata;    // Указатель на данные текстуры
	int              mpf;       // Сколько миллисекунд отображен кадр

	GLUquadricObj *quadratic; // Хранилище для наших квадратичных объектов

	HDRAWDIB      hdd;        // Дескриптор для нашего рисунка
	HBITMAP       hBitmap;    // Дескриптор устройства растра
	HDC hdc = CreateCompatibleDC(0); // Создание совместимого контекста устройства
	unsigned char* data = 0;         // Указатель на наше измененное в размерах изображение

};