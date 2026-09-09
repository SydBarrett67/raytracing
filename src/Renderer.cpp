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
        "Lenia",
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
        SDL_PIXELFORMAT_RGBA8888,
        // Access
        SDL_TEXTUREACCESS_STREAMING,
        this->width,
        this->height
    );

    SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_LINEAR);
    
    return window;
}

void Renderer::render() {
    // Update internal texture 
    SDL_UpdateTexture(
        this->texture,
        nullptr, 
        this->rt.getPixels().data(),
        this->width * 4
    );

    // Present the texture
    SDL_RenderClear(this->renderer);
    SDL_RenderTexture(this->renderer, this->texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}

