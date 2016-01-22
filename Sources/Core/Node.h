#pragma once

#include <string>
#include <map>

namespace Core
{
	class Node
	{
	public:
		Node()		
		{
			//currentNode = Nodes.begin();
		}
		virtual ~Node(){}

		void SetName(const std::string& name_)
		{
			name = name_;
		}

		std::string GetName()
		{
			return name;
		}

		void AddParam(const std::string& key_, const std::string& value_)
		{
			std::string key = key_;
			std::string value = value_;			
			Parameters[key] = value;
		}

		std::string GetParam(const std::string& key)
		{
			std::map<std::string, std::string>::const_iterator ifind = Parameters.find( key );
			
			return ifind->second;
		}

		void AddChild(const Node& node_)
		{
			Nodes.push_back(node_);
		}

		bool GetChildFront(Node& node)
		{
			if (Nodes.empty())
			{
				return false;
			}
			else
			{
				//node = *currentNode;
				//++currentNode;
				node = Nodes.front();
				return true;
			}
		}

		bool GetChild(const std::string& name, Node& node)
		{
			for(auto it = Nodes.begin(); it != Nodes.end(); ++it)
			{
				if (it->GetName() == name)
				{
					node = *it;
					return true;
				}
			}
			return false;
		}

		unsigned NumChild()
		{
			return Nodes.size();
		}
	private:
		std::string name;
		std::map<std::string, std::string> Parameters;
		std::list<Node> Nodes;
		std::list<Node>::iterator currentNode;
	};
}