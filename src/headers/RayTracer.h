#pragma once

#include "headers/vec3.h"
#include "headers/Ray.h"
#include "headers/Camera.h"

#include <vector>

class RayTracer
{
private:
    // Dimensions
    size_t width;
    size_t height;

    // Pixels
    std::vector<vec3> pixels;

    // Camera
    Camera cam;

    // Config 
    size_t rays_per_pixel;
    size_t bounces;

public:
    RayTracer(size_t width, size_t height, Camera cam, size_t rays_per_pixel=1, size_t bounces=2)
    : width(width), height(height),
    cam(cam),
    pixels(width * height, vec3(0.0f)),
    rays_per_pixel(rays_per_pixel),
    bounces(bounces)
    {};

    // Trace all rays / pixels
    void trace();

    vec3 trace_ray(Ray ray);

    // Gets all pixels
    std::vector<vec3> getPixels() const { return pixels; };
};
