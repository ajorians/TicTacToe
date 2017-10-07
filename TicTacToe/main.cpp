#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "DisplayMetrics.h"
#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

SDL_Renderer* renderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		IMG_Init(IMG_INIT_PNG);

		//Create window
		gWindow = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Setup renderer
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	int boardDimension = 3;
	if (argc > 1) {
		boardDimension = std::stoi(args[1]);
	}

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		DisplayMetrics metrics{ SCREEN_WIDTH, SCREEN_HEIGHT };
		Game g{ renderer, &metrics, boardDimension };
		while (g.Loop(renderer))
		{
			//Update the surface
			SDL_UpdateWindowSurface(gWindow);

			//Wait
			SDL_Delay(30);
		}
	}

	//Free resources and close SDL
	close();

	exit(0);
}