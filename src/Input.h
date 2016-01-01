#pragma once

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

	bool UpdateKeys(); 
};