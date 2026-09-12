#include <iostream>

// SDL
#include <SDL3/SDL.h>

// Modules
#include "headers/Renderer.h"
#include "headers/Camera.h"
#include "headers/math.h"

#define width 480
#define height 240

#define MOUSE_SENSITIVITY 0.01f

int main()
{
    // Camera construction
    Camera camera = Camera();

    // Scene construction
    Scene scene = Scene({
        // Spheres
        Sphere(vec3(2.0f), 1.0f)
    });

    // Raytracer construction
    RayTracer rt = RayTracer(width, height, &camera, scene);

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
            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                float dx = event.motion.xrel;
                float dy = event.motion.yrel;

                transform_matrix = math::getRotationMatrix(
                    dx * MOUSE_SENSITIVITY,
                    dy * MOUSE_SENSITIVITY
                );

                camera.update(transform_matrix);
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