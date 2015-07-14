﻿#include "Video.h"

//GL_Window*  g_window;
//Video::Keys*      g_keys;

#pragma comment( lib, "vfw32.lib" )    // Искать VFW32.lib при линковке




void Video::flipIt(void* buffer) // Функция меняющая красный и синий цвет
{
	void* b = buffer;     // Указатель на буфер
	__asm                   // Начало asm кода
	{
		mov ecx, 256 * 256    // Установка счётчика (Размер блока памяти)
			mov ebx, b          // Указатель ebx на наши данные (b)
		label :              // Метка для цикла
		mov al, [ebx + 0]    // Загружаем значение из ebx в регистр al
			mov ah, [ebx + 2]    // Загружаем значение из ebx+2 в регистр ah
			mov[ebx + 2], al    // Сохраняем данные в al из ebx+2
			mov[ebx + 0], ah    // Сохраняем данные в ah из ebx

			add ebx, 3         // Перемещаем указатель на три байта
			dec ecx           // Уменьшаем наш счётчик
			jnz label             // Если не равно нулю перемещаемся назад
	}
}

void Video::OpenAVI(LPCSTR szFile)  // Вскрытие AVI файла (szFile)
{
	//TCHAR  title[100];         // Будет содержать заголовок
	AVISTREAMINFO    psi;       // Указатель на структуру содержащую информацию о потоке

	AVIFileInit();             // Открывает файл

	// Открытие AVI потока
	if (AVIStreamOpenFromFile(&pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL) != 0)
	{
		// Если ошибка
		MessageBox(HWND_DESKTOP, "Failed To Open The AVI Stream",
			"Error", MB_OK | MB_ICONEXCLAMATION);
	}

	AVIStreamInfo(pavi, &psi, sizeof(psi));   // Записываем информацию о потоке в psi
	width = psi.rcFrame.right - psi.rcFrame.left; // Ширина = правая граница минус левая
	height = psi.rcFrame.bottom - psi.rcFrame.top;// Высота равна верх минус низ

	lastframe = AVIStreamLength(pavi);          // Последний кадр потока

	// Вычисление приблизительных миллисекунд на кадр
	mpf = AVIStreamSampleToTime(pavi, lastframe) / lastframe;

	bmih.biSize = sizeof(BITMAPINFOHEADER); // Размер BitmapInfoHeader’а
	bmih.biPlanes = 1;       // Размер
	bmih.biBitCount = 24;      // Формат битов
	bmih.biWidth = 256;     // Ширина(256 пикселов)
	bmih.biHeight = 256;     // Высота(256 пикселов)
	bmih.biCompression = BI_RGB;  // Цветовой режим (RGB)

	hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)(&bmih),
		DIB_RGB_COLORS, (void**)(&data), NULL, NULL);
	SelectObject(hdc, hBitmap);   // Выбор hBitmap в наш контекст устройства (hdc)

	pgf = AVIStreamGetFrameOpen(pavi, NULL); // Создание PGETFRAME с нужными нам параметрами
	if (pgf == NULL)
	{
		// Если ошибка
		MessageBox(HWND_DESKTOP, "Failed To Open The AVI Frame",
			"Error", MB_OK | MB_ICONEXCLAMATION);
	}

	// Информация для заголовка (Ширина/Высота/Кол-во кадров)
	//wsprintf(title, "NeHe's AVI Player: Width: %d, Height: %d, Frames: %d",
//		width, height, lastframe);
	//SetWindowText(g_window->hWnd, title);  // Изменение заголовка
}

void Video::GrabAVIFrame(int frame) // Захват кадра
{
	LPBITMAPINFOHEADER lpbi;  // Содержит BitmapInfoHeader
	// Получение данных из потока
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);
	// Указатель на данные возвращенные AVIStreamGetFrame
	// (Пропуск заголовка для получения указателя на данные)
	pdata = (char *)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);
	// Преобразование информации в нужный нам формат
	DrawDibDraw(hdd, hdc, 0, 0, 256, 256, lpbi, pdata, 0, 0, width, height, 0);

	flipIt(data); // Перестановка красных и синих байтов

	// Обновление текстуры
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void Video::CloseAVI()             // Функция закрытия
{
	DeleteObject(hBitmap);        // Уничтожение устройства растра
	DrawDibClose(hdd);            // Закрытие контекста DrawDib устройства
	AVIStreamGetFrameClose(pgf);  // Закрытие объекта GetFrame
	AVIStreamRelease(pavi);       // Завершение потока
	AVIFileExit();                // Закрытие файла
}

bool Video::Initialize() //Инициализация
{
	//g_window = window;
	//g_keys = keys;

	// Начало инициализации
	angle = 0.0f;                             // Установка угла в ноль
	hdd = DrawDibOpen();                      // Получение контекста устройства
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);    // Черный фон
	glClearDepth(1.0f);                      // Установка буфера глубины
	glDepthFunc(GL_LEQUAL);                  // Тип тестирования глубины (Less или Equal)
	glEnable(GL_DEPTH_TEST);                  // Включение теста глубины
	glShadeModel(GL_SMOOTH);                 // Выбор гладкости
	// Очень аккуратная установка перспективы
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	quadratic = gluNewQuadric();                // Создание нового квадратичного объекта
	gluQuadricNormals(quadratic, GLU_SMOOTH); // Сглаженные нормали
	gluQuadricTexture(quadratic, GL_TRUE);    // Создание текстурных координат

	glEnable(GL_TEXTURE_2D); // Включение двухмерных текстур
	// Установка фильтра увеличения текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Установка фильтра уменьшения текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Включение автогенерации текстурных координат по координате S сферического наложения
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	// Включение автогенерации текстурных координат по координате T сферического наложения
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	OpenAVI("Face2.avi");          // Откроем видео-файл

	// Создание текстуры
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return true; //Возвращение true (инициализация успешна)
}

void Video::Deinitialize(void) //Вся деиницилизация здесь
{
	CloseAVI();            // Закрываем AVI
}

void Video::Update(DWORD milliseconds) // Движение обновляется тут
{
	/*
	if (g_keys->keyDown[VK_ESCAPE] == true) // Если ESC нажат
	{
		//TerminateApplication(g_window); // Завершение приложения
	}

	if (g_keys->keyDown[VK_F1] == true) // Если F1 нажата
	{
		//ToggleFullscreen(g_window); // Включение полноэкранного режима
	}

	if ((g_keys->keyDown[' ']) && !sp) // Пробел нажат и не удерживается
	{
		sp = true;      // Установка sp в истину
		effect++;     // Изменение эффекта (увеличение effect)
		if (effect > 3) // Превышен лимит?
			effect = 0;   // Возвращаемся к нулю
	}

	if (!g_keys->keyDown[' ']) // Если пробел отпущен
		sp = false; // Установка sp в false

	if ((g_keys->keyDown['B']) && !bp) // ‘B’ нажат и не удерживается
	{
		bp = true; // Установка bp в true
		bg = !bg;  // Включение фона Off/On
	}

	if (!g_keys->keyDown['B']) // Если ‘B’ отпущен
		bp = false; //Установка bp в false

	if ((g_keys->keyDown['E']) && !ep) // Если ‘E’ нажат и не удерживается
	{
		ep = true;  // Установка ep в true
		env = !env; // Включение отображения среды Off/On
	}

	if (!g_keys->keyDown['E']) // Если 'E' отпущен?
		ep = false;                // Установка ep в false
		*/

	angle += (float)(milliseconds) / 60.0f; // Обновление angle на основе времени

	next += milliseconds;  // Увеличение next основанное на таймере (миллисекундах)
	frame = next / mpf;       // Вычисление текущего кадра
	if (frame >= lastframe) // Не пропустили ли мы последний кадр?
	{
		frame = 0;            // Сбрасываем frame назад в нуль (начало анимации)
		next = 0;             // Сбрасываем таймер анимации (next)
	}

}

void Video::Draw(void)         // Прорисовка сцены
{
	// Очистка экрана и буфера глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GrabAVIFrame(frame);   // Захват кадра анимации

	if (bg)                // Фоновое изображение показывать?
	{
		glLoadIdentity();    // Сброс матрицы просмотра
		glBegin(GL_QUADS);   // Начало прорисовки фонового рисунка
		// Передняя грань
		glTexCoord2f(1.0f, 1.0f); glVertex3f(11.0f, 8.3f, -20.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-11.0f, 8.3f, -20.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-11.0f, -8.3f, -20.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(11.0f, -8.3f, -20.0f);
		glEnd();             // Конец рисования
	}

	glLoadIdentity();     // Сброс матрицы
	glTranslatef(0.0f, 0.0f, -10.0f); // На десять единиц в экран
	if (env)               // Включено отображение эффектов
	{
		glEnable(GL_TEXTURE_GEN_S); // Вкл. автогенерация координат текстуры по S (Новое)
		glEnable(GL_TEXTURE_GEN_T); // Вкл. автогенерация координат текстуры по T (Новое)
	}

	glRotatef(angle*2.3f, 1.0f, 0.0f, 0.0f); // Немного вращает объекты по оси x
	glRotatef(angle*1.8f, 0.0f, 1.0f, 0.0f); // Делает то же самое только по оси y
	glTranslatef(0.0f, 0.0f, 2.0f); // После вращения перемещение

	switch (effect) // Какой эффект?
	{
	case 0: // Эффект  0 - Куб
		glRotatef(angle*1.3f, 1.0f, 0.0f, 0.0f); // Вращение по оси x
		glRotatef(angle*1.1f, 0.0f, 1.0f, 0.0f); // Вращение по оси y
		glRotatef(angle*1.2f, 0.0f, 0.0f, 1.0f); // Вращение по оси z
		glBegin(GL_QUADS); // Начало рисования куба
		//Передняя грань
		glNormal3f(0.0f, 0.0f, 0.5f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		//Задняя грань
		glNormal3f(0.0f, 0.0f, -0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		//Верхняя грань
		glNormal3f(0.0f, 0.5f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		// Нижняя грань
		glNormal3f(0.0f, -0.5f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		// Правая грань
		glNormal3f(0.5f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		// Левая грань
		glNormal3f(-0.5f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();            // Конец рисования нашего куба
		break;              // Конец нулевого эффекта

	case 1: // Эффект 1 - сфера
		glRotatef(angle*1.3f, 1.0f, 0.0f, 0.0f); // Вращение по оси x
		glRotatef(angle*1.1f, 0.0f, 1.0f, 0.0f); // Вращение по оси y
		glRotatef(angle*1.2f, 0.0f, 0.0f, 1.0f); // Вращение по оси z
		gluSphere(quadratic, 1.3f, 20, 20); // Прорисовка сферы
		break; //Конец прорисовки сферы

	case 2: // Эффект 2 - цилиндр
		glRotatef(angle*1.3f, 1.0f, 0.0f, 0.0f);    // Вращение по оси x
		glRotatef(angle*1.1f, 0.0f, 1.0f, 0.0f);    // Вращение по оси y
		glRotatef(angle*1.2f, 0.0f, 0.0f, 1.0f);    // Вращение по оси z
		glTranslatef(0.0f, 0.0f, -1.5f);               // Центр цилиндра
		gluCylinder(quadratic, 1.0f, 1.0f, 3.0f, 32, 32); // Прорисовка цилиндра
		break; //Конец прорисовки цилиндра
	}

	if (env) // Включено наложение окружения?
	{
		glDisable(GL_TEXTURE_GEN_S); // Вкл. автогенерация координат текстуры по S (Новое)
		glDisable(GL_TEXTURE_GEN_T); // Вкл. автогенерация координат текстуры по T (Новое)
	}

	glFlush();              // Визуализация
}
