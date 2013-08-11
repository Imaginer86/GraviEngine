#include "Game.h"

Game::Game(void)
: numOfMasses(0)
, masses(0)
, timeScale(1.0f)
{
}

Game::~Game(void)
{
	delete[] masses;
}

void Game::Update( float eps )
{
	this->operate(eps);
}

void Game::Draw()
{

}
