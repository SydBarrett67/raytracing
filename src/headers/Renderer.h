#pragma once

#include "headers/RayTracer.h"

#include <cstddef>

class Renderer
{
private:
    // Dimensions
    size_t width;
    size_t height;

    // Ray tracer
    RayTracer rt;

    // SDL Textures and Renderer
    SDL_Renderer* renderer;
    SDL_Texture* texture;

public:
    Renderer(size_t width, size_t height, RayTracer rt)
    : width(width),
    height(height),
    rt(rt)
    {
    }

    // Window initialization
    SDL_Window* createWindow();

    // Draw
    void render();

};

