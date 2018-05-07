#include "Menu.h"


//SDL_Renderer* renderer = NULL;

Menu::Menu()
{
}


Menu::~Menu()
{
}

bool Menu::displayMenu(SDL_Renderer* renderer)
{
	int const runNumOfFrames = 4;
	menuExit = true;
	//STATIC IMAGES
	//load surfaces from assets folder
	SDL_Surface* backgroundSurface = IMG_Load("assets/menu/background.png");
	SDL_Surface* startButtonSurface = IMG_Load("assets/menu/startButton.png");
	SDL_Surface* highScoreButtonSurface = IMG_Load("assets/menu/highScoreButton.png");
	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_Texture* startButtonTexture = SDL_CreateTextureFromSurface(renderer, startButtonSurface);
	SDL_Texture* highScoreButtonTexture = SDL_CreateTextureFromSurface(renderer, highScoreButtonSurface);
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(startButtonSurface);
	SDL_FreeSurface(highScoreButtonSurface);
	SDL_FreeSurface(exitButtonSurface);
	
	//destination of background
	SDL_Rect backgroundDesination;
	backgroundDesination.x = 0;
	backgroundDesination.y = 0;
	//destinatin of start button
	SDL_Rect startButtonDestination;
	startButtonDestination.x = 490;
	startButtonDestination.y = 250;
	//startButtonDestination.w = 600;
	//startButtonDestination.h = 200;
	//destination of high score button
	SDL_Rect highScoreButtonDestination;
	highScoreButtonDestination.x = 490;
	highScoreButtonDestination.y = 400;
	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 490;
	exitButtonDestination.y = 550;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundDesination.w, &backgroundDesination.h);
	SDL_QueryTexture(startButtonTexture, NULL, NULL, &startButtonDestination.w, &startButtonDestination.h);
	SDL_QueryTexture(highScoreButtonTexture, NULL, NULL, &highScoreButtonDestination.w, &highScoreButtonDestination.h);
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);
	
	//ANIMATION
	SDL_Texture* runSpriteSheet = IMG_LoadTexture(renderer, "assets/walkingsprite.png");
	//this time, lets makea source rectangle copying just 1 frame in size at a time
	SDL_Rect runClipRect = { 0, 0, 128, 128 };	//x:0, y:0, w:32, h:32
	SDL_Rect runDestRect = { 0, 0, 128, 128 };	//x y, get image to top left of screen. w/h match clip/frame size

												//animation objects
	Animation knight1(runSpriteSheet, renderer, 75, 128, 128, 0.2);	//0.2 = 200 milliseconds per frame of animation;
	Animation knight2(runSpriteSheet, renderer, 75, 128, 128, 0.8);





	SDL_Event e;

	Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time (milliseconds to reach this bit of code)

	while (menuExit)
	{
		//difference is current time running minus the last update time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert into deltaTime (decimal)
		float DT = timeDiff / 1000.0; //e.g 200ms now = 0.2 for DT
		//now update lastUpdate to the current time so the next loop calculates correctly
		lastUpdate = SDL_GetTicks();

		//draw background and menu buttons
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundDesination);
		SDL_RenderCopy(renderer, startButtonTexture, NULL, &startButtonDestination);
		SDL_RenderCopy(renderer, highScoreButtonTexture, NULL, &highScoreButtonDestination);
		SDL_RenderCopy(renderer, exitButtonTexture, NULL, &exitButtonDestination);

		//animations

		//update animations
		knight1.update(DT);
		knight2.update(DT);

		//draw from animations
		knight1.draw(0, 0);
		knight2.draw(220, 100, 2.0f);	//4.0f is scale, stretch by x4

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit loop
				menuExit = false;
			}
			//check if user has pressed a button
			if (e.type == SDL_KEYDOWN)
			{
				//see if ESC key was pressed
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					//exit loop
					menuExit = false;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						menuExit = false;
					}
					else if (e.button.x >= startButtonDestination.x && e.button.x <= startButtonDestination.x + 300 && e.button.y >= startButtonDestination.y && e.button.y <= startButtonDestination.y + 100)
					{
						//START BUTTON THINGS HERE
						cout << "Starting game" << endl;
						characterCreation(renderer);
					}
					else if (e.button.x >= highScoreButtonDestination.x && e.button.x <= highScoreButtonDestination.x + 300 && e.button.y >= highScoreButtonDestination.y && e.button.y <= highScoreButtonDestination.y + 100)
					{
						//BRING UP HIGH SCORE MENU HERE
						cout << "Here is your high score menu" << endl;
						viewHighScores(renderer);
					}
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(startButtonTexture);
	SDL_DestroyTexture(highScoreButtonTexture);
	SDL_DestroyTexture(exitButtonTexture);

	return false;
}

void Menu::characterCreation(SDL_Renderer* renderer)
{
	GameLoop* startGameLoop = new GameLoop();

	//DISPLAY CHARACTER AND ASK PLAYER TO NAME THE CHARACTER
	//ONLY 1 CHARACTER FOR NOW 

	SDL_Surface* backgroundSurface = IMG_Load("assets/menu/background.png");
	SDL_Surface* startButtonSurface = IMG_Load("assets/menu/startButton.png");
	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_Texture* startButtonTexture = SDL_CreateTextureFromSurface(renderer, startButtonSurface);
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(startButtonSurface);
	SDL_FreeSurface(exitButtonSurface);

	//destination of background
	SDL_Rect backgroundDesination;
	backgroundDesination.x = 0;
	backgroundDesination.y = 0;

	//destinatin of start button
	SDL_Rect startButtonDestination;
	startButtonDestination.x = 900;
	startButtonDestination.y = 540;

	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 80;
	exitButtonDestination.y = 540;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundDesination.w, &backgroundDesination.h);
	SDL_QueryTexture(startButtonTexture, NULL, NULL, &startButtonDestination.w, &startButtonDestination.h);
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);

	
	//loop to controll the character creation
	bool startGame = true;

	SDL_Event e;

	while (startGame)
	{
		//place background again
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundDesination);

		//place UI elements
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);

		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 620 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);

		//place animated hero

		//place left and right arrows to change hero (FOR LATER IMPLEMENTATION OF DIFFERENT HEROS AND COLOUR SHCHEMES)

		//inform user to input a name in a text box 

		//place start and back button
		SDL_RenderCopy(renderer, startButtonTexture, NULL, &startButtonDestination);
		SDL_RenderCopy(renderer, exitButtonTexture, NULL, &exitButtonDestination);


		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit game
				startGame = false;
				//SDL_Quit();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						startGame = false;
					}
					else if (e.button.x >= startButtonDestination.x && e.button.x <= startButtonDestination.x + 300 && e.button.y >= startButtonDestination.y && e.button.y <= startButtonDestination.y + 100)
					{
						//START BUTTON THINGS HERE
						cout << "Character Creation complete!" << endl;
						startGame = false;
						startGameLoop->runGameLoop(renderer);
					}
				}
			}
		}

		//gameLoop->runGameLoop(renderer);
		SDL_RenderPresent(renderer);
	}
	//clean up textures before exiting
	SDL_DestroyTexture(backgroundTexture);
}

void Menu::viewHighScores(SDL_Renderer* renderer)
{
	//DISPLAY LEADERBOARD OF HIGH SCORES
	//SCORE IS BASED ON HOW MUCH MONEY IS COLLECTED ON A VICTORY RUN (BEAT THE GAME)
	SDL_Surface* backgroundSurface = IMG_Load("assets/menu/background.png");
	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(exitButtonSurface);

	//destination of background
	SDL_Rect backgroundDesination;
	backgroundDesination.x = 0;
	backgroundDesination.y = 0;

	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 80;
	exitButtonDestination.y = 540;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundDesination.w, &backgroundDesination.h);
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 32);	//params: font file, font size

	SDL_Color textColor = { 255, 255,255, 0 };


	//create a surface using this fonr to display some sort of message
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "High Scores", textColor);
	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//delete surface properly
	SDL_FreeSurface(textSurface);

	//text destination
	SDL_Rect textDestination;
	textDestination.x = 1280/2 - (textSurface->w / 2);
;	textDestination.y = 50;
	//get width and height from texture and set it for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);


	SDL_Event e;
	bool displayHighScores = true;

	while (displayHighScores)
	{
		// place background again
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundDesination);

		//place UI elements
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 620 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);
		//place start and back button
		SDL_RenderCopy(renderer, exitButtonTexture, NULL, &exitButtonDestination);

		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit game
				displayHighScores = false;
				//SDL_Quit();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						displayHighScores = false;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
}