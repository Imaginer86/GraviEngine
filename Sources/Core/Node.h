#pragma once

#include <string>
#include <map>
#include <list>

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

		unsigned SizeParam()
		{
			return Parameters.size();
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

		unsigned SizeChild()
		{
			return Nodes.size();
		}

		void AddChild(const Node& node_)
		{
			Nodes.push_back(node_);
		}

		bool GetNode(const std::string& name_, Node& node_)
		{
			if (name_ == name)
			{
				node_ = *this;
				return true;
			}
			else
			{
				Node nodeChild;
				if (GetChild(name_, nodeChild))
				{
					node_= nodeChild;
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		bool GetChildFront(Node& node)
		{
			if (Nodes.empty())
			{
				return false;
			}
			else
			{
				node = Nodes.front();
				return true;
			}
		}

		bool GetChild(const std::string& name_, Node& node_)
		{
			for(auto it = Nodes.begin(); it != Nodes.end(); ++it)
			{
				if (it->GetName() == name_)
				{
					node_ = *it;
					return true;
				}
			}
			for(auto it = Nodes.begin(); it != Nodes.end(); ++it)
			{
				Node nodeChild;				
				if (it->GetChild(name_, nodeChild))
				{
					node_ = nodeChild;
					return true;
				}
			}
			return false;
		}

	private:
		std::string name;
		std::map<std::string, std::string> Parameters;
		std::list<Node> Nodes;
	};
}