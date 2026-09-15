#include <iostream>

// SDL
#include <SDL3/SDL.h>

// Modules
#include "headers/Renderer.h"
#include "headers/Camera.h"
#include "headers/math.h"
#include "headers/ObjParser.h"

#include "headers/Object.h"
#include "headers/Mesh.h"
#include "headers/Sphere.h"

#define width 800
#define height 400

#define MOUSE_SENSITIVITY 0.01f
#define CAMERA_SPEED 0.1f

int main()
{

    ObjParser objparser = ObjParser();

    // Camera construction
    Camera camera = Camera(vec3(0.0f));

    // Scene construction
    Scene scene = Scene({
        // Spheres
        std::make_shared<Sphere>(vec3(5.0f), 1.0f, vec3(0.5f, 0.5f, 1.0f), 1.0f),
        std::make_shared<Sphere>(vec3(7.0f, 2.0f, 3.0f), 2.0f, vec3(1.0f, 0.2f, 0.5f)),
        std::make_shared<Sphere>(vec3(2.0f), 2.5f, vec3(0.1f, 1.0f, 0.5f)),

        // Test cube
        std::make_shared<Mesh>(objparser.parse("tests/cube.obj"))
    });

    // Raytracer construction
    RayTracer rt = RayTracer(width, height, &camera, &scene, 1, 5);

    // Renderer construction
    Renderer renderer = Renderer(width, height, rt);

    // Window creation
    SDL_Window* window = renderer.createWindow();

    // Main loop
    bool running = true;

    const bool* keystate = SDL_GetKeyboardState(NULL);

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
            // Movement
            if (keystate[SDL_SCANCODE_W]) {
                camera.position = camera.position + camera.orientation * CAMERA_SPEED;
            }
            if (keystate[SDL_SCANCODE_S]) {
                camera.position = camera.position - camera.orientation * CAMERA_SPEED;
            }
            if (keystate[SDL_SCANCODE_A]) {
                vec3 right = math::cross(camera.orientation, vec3(0.0f, 1.0f, 0.0f));
                right.normalize();
                camera.position = camera.position - right * CAMERA_SPEED;
            }
            if (keystate[SDL_SCANCODE_D]) {
                vec3 right = math::cross(camera.orientation, vec3(0.0f, 1.0f, 0.0f));
                right.normalize();
                camera.position = camera.position + right * CAMERA_SPEED;
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