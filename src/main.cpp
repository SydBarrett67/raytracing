#include <iostream>

// SDL
#include <SDL3/SDL.h>

// Modules
#include "headers/Renderer.h"
#include "headers/Camera.h"
#include "headers/math.h"

#define width 800
#define height 400

#define MOUSE_SENSITIVITY 0.01f

int main()
{
    // Camera construction
    Camera camera = Camera(vec3(1.0f));

    // Scene construction
    Scene scene = Scene({
        // Spheres
        Sphere(vec3(5.0f), 1.0f, vec3(0.5f, 0.5f, 1.0f)),
        Sphere(vec3(7.0f, 2.0f, 3.0f), 2.0f, vec3(1.0f, 0.2f, 0.5f)),

    });

    // Raytracer construction
    RayTracer rt = RayTracer(width, height, &camera, &scene);

    // Renderer construction
    Renderer renderer = Renderer(width, height, rt);

    // Window creation
    SDL_Window* window = renderer.createWindow();

    // Main loop
    bool running = true;
    mat3 transform_matrix;

    while (running) {
        // Event loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Mouse movement
            if (event.type == SDL_EVENT_MOUSE_MOTION)
            {
                camera.update(
                    event.motion.xrel * MOUSE_SENSITIVITY,
                    event.motion.yrel * MOUSE_SENSITIVITY
                );
            }

            // Quit event
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