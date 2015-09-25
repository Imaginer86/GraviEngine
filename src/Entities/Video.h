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


};