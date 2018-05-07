#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


class GameLoop
{
public:
	bool gameExit;

	GameLoop();
	~GameLoop();

	bool runGameLoop(SDL_Renderer* renderer);

};

