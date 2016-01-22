#pragma once

#include <list>
#include <string>
#include <fstream>

#include "Node.h"

namespace Core
{
	class FileStream
	{
	public:

		FileStream();
		virtual ~FileStream(){};

		bool OpenRead(const std::string& fileName);
		bool OpenWrite(const std::string& fileName);

		bool OpenXML(const std::string& fileName);

		bool ReadNode(Node& node_);

		void Close();

		std::string GetLine();

		bool GetNode(Node& node_);
		bool GetNode(std::string& node, const std::string& name);
	private:
		Node node;
		//std::list<Node>::iterator currentNode;

		std::fstream file;		
	};

	inline FileStream::FileStream()
	{
		//Nodes.clear();
		//currentNode = Nodes.begin();
	};
}