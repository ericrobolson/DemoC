#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "gmain_loop.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Frees media and shuts down SDL
void sdl_close();

//The window we'll be rendering to
SDL_Window *window = NULL;

// Renderer
SDL_Renderer *renderer = NULL;

// The event we use for polling.
SDL_Event event;

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
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            printf("renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

void sdl_close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

// Render method.
void render(GState state, double delta_t)
{
    // Init new render
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Execute render code
    int i = 0;
    int x, y, w, h;
    u8 r, g, b, a;
    GColor color;

    for (i = 0; i < state.max_entities; i++)
    {
        if (state.entities[i] == false)
        {
            continue;
        }

        x = state.positions[i].x;
        y = (int)state.positions[i].y;
        w = (int)state.aabbs[i].width;
        h = (int)state.aabbs[i].height;
        color = state.colors[i];

        SDL_Rect fillRect = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &fillRect);
    }

    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}

// Poll events.
bool poll_events()
{
    bool successful = SDL_PollEvent(&event) != 0;
    switch (event.type)
    {
    case SDL_QUIT:
        return false;
        break;
    }
    return true;
}

int main(int argc, char *args[])
{

    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }

    // Start the main loop.
    gmain_loop(&poll_events, &render);

    //Free resources and close SDL
    sdl_close();

    return 0;
}
