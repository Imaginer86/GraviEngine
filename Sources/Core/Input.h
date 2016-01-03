#pragma once

namespace Core
{

	class Input
	{
	public:
		Input(){}
		virtual ~Input(){}

		static Input& Instance()
		{
			static Input SingleInput;
			return SingleInput;
		}

		void UpdateKeys(); 
	};

}