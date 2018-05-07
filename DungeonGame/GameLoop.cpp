#include "GameLoop.h"



GameLoop::GameLoop()
{
}


GameLoop::~GameLoop()
{
}

bool GameLoop::runGameLoop(SDL_Renderer* renderer)
{
	gameExit = true;

	while (gameExit)
	{
		gameExit = false;
	}

	return gameExit;
}
