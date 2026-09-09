#include <iostream>

// SDL
#include <SDL3/SDL.h>

// Modules
#include "headers/Renderer.h"

#define width 480
#define height 240

int main()
{
    // Raytracer construction
    RayTracer rt = RayTracer();

    // Renderer construction
    Renderer renderer = Renderer(width, height, rt);

    // Window creation
    SDL_Window* window = renderer.createWindow();

    // Main loop
    bool running = true;
    while (running) {

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        renderer.render();
    }


    // Window destruction
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}