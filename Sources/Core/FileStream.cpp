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
	file.open(fileName, std::ios::in);
	if (file.is_open())
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
	//if (currentNode == Nodes.end())
	//{
		//return false;
	//}

	node_ = node;
	//++currentNode;
	return true;
}

bool FileStream::ReadNode(Node& node_)
{
	Node nodeX;
	std::string str;
	for(file >> str; !file.eof() && (str.find('>') == -1 || str.size() > 1) ;file >> str)
	{	
		std::cout << str << " ";
		int f = str.find('<');
		std::cout << "f " << f << " ";
		if ( f > -1)
		{
			std::string name(str.c_str() + 1, str.size());
			nodeX.SetName(name);
			std::cout << name << std::endl;

			file >> str;
			std::cout << str << " ";
		
				
			if (str.find('<') > -1)
			{
				Node nodeChild;
				while(ReadNode(nodeChild))
				{
					nodeX.AddChild(nodeChild);
				}
			}
			else
			{
				int pos;
				if ( (pos = str.find('=')) > -1)
				{
					std::string value(str.c_str() + pos + 2, str.size() - pos + 1);
					std::string key(str.c_str(), pos);						
					
					nodeX.AddParam(key, value);
				}
			}
		}
		node_  = nodeX;
	}
	std::cout << std::endl;
	return true;
}