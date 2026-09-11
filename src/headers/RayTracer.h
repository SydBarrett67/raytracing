#pragma once

#include "headers/vec3.h"
#include "headers/Ray.h"
#include "headers/Camera.h"
#include "headers/Scene.h"

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

    // Scene
    Scene scene;

    // Config 
    size_t rays_per_pixel;
    size_t bounces;

public:
    RayTracer(size_t width, size_t height, Camera cam, Scene scene = Scene(), size_t rays_per_pixel=1, size_t bounces=2)
    : width(width), height(height),
    cam(cam),
    pixels(width * height, vec3(0.0f)),

    rays_per_pixel(rays_per_pixel),
    bounces(bounces)
    {};

    // Trace all rays / pixels
    void trace();

    vec3 trace_ray(Ray ray);

    // Gets all pixels in byte format
    std::vector<uint8_t> getPixels() const { 
        std::vector<uint8_t> bytes;

        for (auto& px : pixels) {
            bytes.push_back(
                static_cast<uint8_t>(px.x * 255.0f) // R
            );
            bytes.push_back(
                static_cast<uint8_t>(px.y * 255.0f) // G
            );
            bytes.push_back(
                static_cast<uint8_t>(px.z * 255.0f) // B
            );
            bytes.push_back(
                static_cast<uint8_t>(255.0f)        // A
            );
        }

        return bytes;
    };
};
