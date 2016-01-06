#include "Game.h"
#include "../Sources/Core/Master.h"


void main()
{
	Game gGame = Game::Instance();
	gGame.LoadData(3);

	Core::Master::Instance().Init((GameBase*) &gGame);
	Core::Master::Instance().Run();
	Core::Master::Instance().Release();
}