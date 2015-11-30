#pragma once

class Platform
{
public:

	static const Platform& Instance()
	{
		static Platform TheSingleInstance;
		return TheSingleInstance;
	}


private:
		Platform(){}
		virtual ~Platform(){}
};