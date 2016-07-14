#pragma once

//#include <list>
#include <string>
#include <fstream>

#include "Node.h"
#include "../Math/Vector2f.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"
#include "../Math/Color.h"

namespace Core
{
	class FileStream
	{
	public:

		FileStream(){};
		virtual ~FileStream(){};

		bool OpenRead(const std::string& fileName);
		bool OpenWrite(const std::string& fileName);

		//bool OpenXML(const std::string& fileName);

		void Close();

		bool Eof();

		//bool ReadNode(Node& node_, const std::string& str0 = "");

		//bool GetNode(Node& node_);
		//bool GetNode(std::string& node, const std::string& name);

		std::string GetString();
		bool GetBool();
		float GetFloat();
		unsigned GetUnsigned();
		Vector2f GetVector2f();
		Vector3f GetVector3f();
		Quaternion GetQuaternion();
		Math::Color4f GetColor();
		bool GetParameter(const std::string& paramName);
	private:

		//Node node;
		std::fstream file;
		//std::filebuf fileBuf;;
	};
}