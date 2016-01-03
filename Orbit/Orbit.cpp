#include "Game.h"
#include "../Sources/Core/Master.h"

GameBase *gGame = new Game;

void main()
{
	// Init
	Core::Master::Instance().Init((GameBase*)gGame);

	// Run
	Core::Master::Instance().Run();

	// Shutdown
	Core::Master::Instance().Release();
}