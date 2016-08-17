#include <iostream>

#include "Game.h"
#include "Core/Master.h"

void main()
{
	if (Game::Instance().LoadData("data/data1.dat"))
	{
		if (Core::Master::Instance().Init(&Game::Instance()))
		{
			Game::Instance().initialize();
			Core::Master::Instance().Run();
			Core::Master::Instance().Release();			
		}
		else
		{
			std::cerr << "Error Init Core::Master" << std::endl;
		}

	}
	else
	{
		std::cerr << "Error LoadData" << std::endl;
	}
}