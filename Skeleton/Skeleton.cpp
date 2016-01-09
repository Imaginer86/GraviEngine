#include "Game.h"
#include "../Sources/Core/Master.h"

void main()
{
	Game gGame = Game::Instance();
	gGame.SetSceneName("data/data4.dat");
	gGame.LoadData(gGame.GetSceneName());

	//Core::Master master = Core::Master::Instance();

	Core::Master::Instance().Init((GameBase*) &gGame);
	Core::Master::Instance().Run();
	Core::Master::Instance().Release();
}