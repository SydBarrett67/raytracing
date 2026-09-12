#include <iostream>

// SDL
#include <SDL3/SDL.h>

// Custom modules
#include "headers/Renderer.h"

// Window / Renderer / Texture init wrapper 
SDL_Window* Renderer::createWindow() {
    // Window initialization
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "Raytracer",
        this->width,
        this->height,
        0
    );

    this->renderer = SDL_CreateRenderer(
        window,
        nullptr
    );

    // Create texture
    this->texture = SDL_CreateTexture(
        this->renderer,
        // Pixel format 
        SDL_PIXELFORMAT_RGBA32,
        // Access
        SDL_TEXTUREACCESS_STREAMING,
        this->width,
        this->height
    );

    SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_LINEAR);
    
    return window;
}

void Renderer::render()
{
    this->rt.trace();
    auto pixels = this->rt.getPixels();

    // Update internal texture 
    SDL_UpdateTexture(
        this->texture,
        nullptr,
        pixels.data(),
        this->width * 4
    );

    SDL_RenderClear(this->renderer);
    SDL_RenderTexture(this->renderer, this->texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}
