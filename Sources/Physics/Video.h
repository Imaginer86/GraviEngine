#pragma once

#include <string>

#include "Plane.h"

namespace Physics
{
	class Video: public Plane
	{
	public:

		// These Are The Function You Must Provide
		bool Initialize(const std::string& szFile);	// Performs All Your Initialization

		void Deinitialize(void);							// Performs All Your DeInitialization

		void Update(unsigned long milliseconds);					// Perform Motion Updates

		virtual void Draw(void);									// Perform All Your Scene Drawing
	private:
		void flipIt(void* buffer); // Функция меняющая красный и синий цвет
		void OpenAVI(const std::string& szFile);  // Вскрытие AVI файла (szFile)
		void GrabAVIFrame(int frame); // Захват кадра
		void CloseAVI();             // Функция закрытия
	};

}