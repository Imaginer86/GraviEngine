#include "FileStream.h"

using namespace Core;

bool FileStream::OpenRead(const std::string& fileName)
{
	file.open(fileName, std::ios::in);
	if (file.is_open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FileStream::OpenWrite(const std::string& fileName)
{
	file.open(fileName, std::ios::out);
	if (file.is_open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FileStream::Close()
{
	file.close();
}

std::string FileStream::GetLine()
{
	std::string str;
	std::getline(file, str);
	return str;
}