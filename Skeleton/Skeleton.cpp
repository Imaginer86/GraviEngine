// Skeleton.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
//int _tmain(int argc, _TCHAR* argv[])
//{
	//return 0;
//}


#include "Game.h"
#include "../Sources/Core/Master.h"

void main()
{
	if (Game::Instance().LoadData("data/data2.dat"))
	{
		Core::Master::Instance().Init(&Game::Instance());
		Core::Master::Instance().Run();
		Core::Master::Instance().Release();
	}
}

