#include "FileStream.h"

#include <iostream>

using namespace Core;
using namespace Math;

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

//bool FileStream::OpenXML(const std::string& fileName)
//{
//	std::cout << "Open X3D " <<  fileName << std::endl;
	
	//fileBuf.open(fileName, std::ios::in);
//	if (OpenRead(fileName))
//	{
//		Node node_;
//		while(ReadNode(node_))
//		{
//			std::cout << node_.GetName() << std::endl;
			//return false;
//		}
//		node = node_;
///		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

void FileStream::Close()
{
	file.close();
}

bool FileStream::Eof()
{
	return file.eof();
}

std::string FileStream::GetString()
{
	std::string str;
	file >> str;
	return str;
}

bool FileStream::GetBool()
{
	bool res = false;
	file >> res;
	return res;
}

float FileStream::GetFloat()
{
	float res;
	file >> res;
	return res;
}

unsigned FileStream::GetUnsigned()
{
	unsigned res;
	file >> res;
	return res;
}

Vector2f FileStream::GetVector2f()
{
	float x, y;
	file >> x >> y;
	Vector2f res(x, y);
	return res;
}

Vector3f FileStream::GetVector3f()
{
	float x, y, z;
	file >> x >> y >> z;
	Vector3f res(x, y, z);
	return res;
}

Quaternion FileStream::GetQuaternion()
{
	float x, y, z, w;
	file >> x >> y >> z >> w;
	Quaternion res(w, x, y, z);
	return res;
}

Math::Color4f FileStream::GetColor()
{
	float r, g, b, a;
	file >> r >> g >> b >> a;
	Math::Color4f res(r, g, b, a);
	return res;
}

bool FileStream::GetParameter(const std::string& paramName)
{
	std::string str;
	do
		file >> str;
	while (!Eof() && str.find(paramName) == std::string::npos);	
	if (Eof())
		return true;
	else
		return false;
}

//bool FileStream::GetNode(Node& node_)
//{
	//node_ = node;
	//return true;
//}

//bool FileStream::ReadNode(Node& node_, const std::string& str0)
//{
//todo
/*
	std::string str;
	if (str0 == std::string(""))
		file >> str;
	if (str[0] != '<') 
		return false;
	std::string nodeName = str.substr(1);
	node_.SetName(nodeName);
	str = std::string("");

	std::string strAdd;
	do
	{
		file >> strAdd;
		if (strAdd.find('<') != std::string::npos)
		{
			Node nodeX;
			if (!ReadNode(nodeX, strAdd))
				return false;
			node_.AddChild(nodeX);
			file >> strAdd;
		}
		str += std::string(" ") + strAdd;
	} while (!strAdd.empty() && strAdd.find('>') == std::string::npos);

	std::string key = str.substr(std::size_t(0), str.find('='));
	std::string value = str.substr(str.find('=') + 2, str.length() - 4);
	node.AddParam(key, value);
	std::cout << "key " << key << std::endl;
	std::cout << "value " << value << std::endl;
*/

//while (str.find('>') == std::string::npos);
	/*
		else
		{
			int find2 = str.find('>');
			if (find2 > -1)
			{
				//node_.AddChild(nodeX);
				//std::cout << "Add " << node_.GetName() << " Child " << nodeX.GetName() << std::endl;
				//return true;

			}
			else
			{
				std::cerr << "Cann't Read Node" << std::endl;
				return false;
			}
		}
		//find = str.find('<');
	}
	*/

//}