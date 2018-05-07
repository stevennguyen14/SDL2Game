#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Menu.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char **argv)
{
	//init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Fail initialised!!!\n";
		return -1; //failed, dont continue rest of main code
	}
	else
	{
		cout << "SDL initialised success!!!\n";
	}

	//NEED TO INIT SDL_Image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//create window, params are: window title, window pos x, pos y, width, height, window flags
	window = SDL_CreateWindow("DungeonGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN/* SDL_WINDOW_FULLSCREEN */);
	if (window != NULL) {
		cout << "Window created!" << endl;
	}
	else
	{
		cout << "Failed to create window!" << endl;
		return -1;
	}

	//create renderer to help draw stuff to the screen
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//allow for transparancy or use of alpha on sdl set colour
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if (renderer != NULL)
	{
		cout << "Renderer created!" << endl;
	}
	else
	{
		cout << "Renderer FAILED!" << endl;
		return -1;
	}

	//INIT sdl ttf
	if (TTF_Init() != 0)
	{
		//if failed, complain about it
		cout << "SDL TTF FAILED!" << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	

	Menu *menu = new Menu();


	//displayMenu Returns a false boolean which exits the loop and game
	menu->displayMenu(renderer);
	
	delete menu;

	//destroy window
	SDL_DestroyWindow(window);
	//destroy texures
	//quit
	SDL_Quit;
	return 0;
}