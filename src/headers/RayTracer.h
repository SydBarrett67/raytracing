#pragma once

#include "headers/vec3.h"
#include "headers/Ray.h"

#include <vector>

class RayTracer
{
private:
    std::vector<vec3> pixels;
    size_t rays_per_pixel;
    size_t bounces;
public:
    RayTracer(size_t width, size_t height, size_t rays_per_pixel=1, size_t bounces=2)
    : pixels(width * height, vec3(0.0f)),
    rays_per_pixel(rays_per_pixel),
    bounces(bounces)
    {};

    void trace();

    // Gets all pixels
    std::vector<vec3> getPixels() const { return pixels; };
};
