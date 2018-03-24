/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "AEAsteroid.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <sstream>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

int main(int argc, char* argv[])
{
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	bool bQuit = false;
	SDL_Event e;

	srand(time(NULL));

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		Window = SDL_CreateWindow("Asteroid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(Window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(Window);

			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

			//Wait one seconds
			SDL_Delay(1000);
		}
	}

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	int AsteroidsOnScreen;

	std::vector<AEAsteroid*> mAsteroids;

	if (argc >= 2)
	{
		std::istringstream iss(argv[1]);
		int val;

		if (iss >> val)
		{
			AsteroidsOnScreen = val;
		}
		else
		{
			AsteroidsOnScreen = 10;
		}
	}
	else
	{
		AsteroidsOnScreen = 10;
	}
	for (size_t i = 0; i < AsteroidsOnScreen; i++)
	{
		mAsteroids.push_back(new AEAsteroid());
		mAsteroids[i]->SetRenderer(Renderer);
		mAsteroids[i]->SetRadius(rand() % 50 + 15);
		mAsteroids[i]->GenerateAsteroid(rand() % 5 + 5, rand() % 15 + 5, rand() % 15 + 10);
		mAsteroids[i]->SetVelocityRandomDirection(0.05, 0.05);
		mAsteroids[i]->SetLocation(rand() % 800, rand() % 600);
	}

	while (!bQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				bQuit = true;
			}
		}
		
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Renderer);

		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

		for (size_t i = 0; i < mAsteroids.size(); i++)
		{
			mAsteroids[i]->Update(deltaTime);
			mAsteroids[i]->Rotate(0.1f * deltaTime);
			mAsteroids[i]->Draw();
		}

		SDL_RenderPresent(Renderer);
	}

	for (size_t i = 0; i < mAsteroids.size(); i++)
	{
		delete mAsteroids[i];
	}

	//Destroy window
	SDL_DestroyRenderer( Renderer );
	SDL_DestroyWindow( Window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}