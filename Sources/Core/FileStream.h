#pragma once

#include <fstream>
#include <string>

namespace Core
{

	class FileStream
	{
		public:
		FileStream();
		virtual ~FileStream();

		bool OpenRead(const std::string& fileName);
		bool OpenWrite(const std::string& fileName);
		void Close();
		std::string GetLine();
	private:
		std::fstream file;
	};

	inline FileStream::FileStream()
	{
	}

	inline FileStream::~FileStream()
	{
	}
}