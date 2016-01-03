#include "Game.h"
#include "../Sources/Core/Master.h"

void main()
{
	Game gGame = Game::Instance();
	gGame.LoadData(1);

	Core::Master gMaster = Core::Master::Instance();
	gMaster.Init((GameBase*) &gGame);
	gMaster.Run();
	gMaster.Release();
}