#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Window",
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  680, 480,
										  0);
	if (!window)
	{
		printf("Error initializing SDL window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface *window_surface = SDL_GetWindowSurface(window);

	if (!window_surface)
	{
		printf("Failed to get window surface: %s\n", SDL_GetError());
		return 1;
	}

	printf("Success.\n");
	SDL_Quit();
	return 0;
}
