#include "FileStream.h"

#include <iostream>

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

bool FileStream::OpenXML(const std::string& fileName)
{
	std::cout << "Open X3D " <<  fileName << std::endl;
	
	//fileBuf.open(fileName, std::ios::in);
	if (OpenRead(fileName))
	{
		Node node_;
		while(ReadNode(node_))
		{
			std::cout << node.GetName() << std::endl;
			return false;
		}
		node = node_;
		return true;
	}
	else
	{
		return false;
	}
}

void FileStream::Close()
{
	std::cout << "Close X3D." << std::endl;
	file.close();
}

std::string FileStream::GetLine()
{
	std::string str;
	file >> str;
	return str;
}

bool FileStream::GetNode(Node& node_)
{
	node_ = node;
	return true;
}

bool FileStream::ReadNode(Node& node_)
{
	std::string str;
	file >> str;
	int find = str.find('<');
	if (find == -1)
	{
		return false;
	}
	else
	{
		while (find > -1)
		{
			std::string nodeName = std::string(str.c_str() + 1, str.size() - 1);
			Node nodeX;
			nodeX.SetName(nodeName);
			std::string key;
			std::string value;

			file >> str;

			int find1 = str.find('=');
			if (find1 > -1)
			{
				key = std::string(str.c_str(), find1);
				value = std::string(str.c_str() + find1, str.size() - find1);
				nodeX.AddParam(key, value);
				std::cout << "key " << key << std::endl;
				std::cout << "value " << value << std::endl;
			}
			else
			{
				int find2 = str.find('>');
				if (find2 > -1)
				{
					node_.AddChild(nodeX);
					std::cout << "Add " << node_.GetName() << " Child " << nodeX.GetName() << std::endl;
					//return true;

				}
				else
				{
					std::cerr << "Cann't Read Node" << std::endl;
					return false;
				}
			}

			find = str.find('<');
		}
		return true;
	}

}