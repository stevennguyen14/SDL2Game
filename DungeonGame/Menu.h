#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameLoop.h"
#include "Animation.h"

using namespace std;

class Menu
{
public:
	bool menuExit;

	Menu();
	~Menu();

	bool displayMenu(SDL_Renderer* renderer);
	void characterCreation(SDL_Renderer* renderer);
	void viewHighScores(SDL_Renderer* renderer);

};

