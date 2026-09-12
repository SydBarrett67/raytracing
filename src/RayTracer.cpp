#include <algorithm>
#include <iostream>

#include "headers/RayTracer.h"
#include "headers/Ray.h"
#include "headers/math.h"
#include "headers/mat3.h"

void RayTracer::trace() {
    if (this->frame > 0) return;
    // Loop over every pixel
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {

            // Trace single ray
            this->pixels.at(i * width + j) = this->trace_ray(
                // Init ray from camera position and orientation
                Ray(
                    this->cam.position,
                    this->getRayDirection(j, i)
                )
            );
        }
    }
    // Update frame counter
    this->frame++;
}

vec3 RayTracer::trace_ray(Ray ray) {

    // Loop through every object in the scene and check intersection
    /*
    for (auto& obj : this->scene.objects) {
        if (ray.intersects(obj)) {
            std::cout << "Hit!" << std::endl;
            return vec3(1.0f);
        }
    }

    return vec3(0.0f);
    */

    return ray.dir;
}

std::vector<uint8_t> RayTracer::getPixels()
{
    std::vector<uint8_t> bytes;
    bytes.reserve(width * height * 4);

    for (const auto& px : pixels) {
        uint8_t r = static_cast<uint8_t>(std::clamp((px.x * 0.5f + 0.5f) * 255.0f, 0.0f, 255.0f));
        uint8_t g = static_cast<uint8_t>(std::clamp((px.y * 0.5f + 0.5f) * 255.0f, 0.0f, 255.0f));
        uint8_t b = static_cast<uint8_t>(std::clamp((px.z * 0.5f + 0.5f) * 255.0f, 0.0f, 255.0f));

        bytes.push_back(r);
        bytes.push_back(g);
        bytes.push_back(b);
        bytes.push_back(255);
    }

    return bytes;
}
vec3 RayTracer::getRayDirection(int x, int y)
{
    float aspect_ratio = (float)width / height;

    // Coordinate normalizzate [-1, 1]
    float px = (2.0f * ((x + 0.5f) / width) - 1.0f);
    float py = (1.0f - 2.0f * ((y + 0.5f) / height));

    px *= aspect_ratio;

    vec3 world_up(0.0f, 1.0f, 0.0f);

    // 1. Forward deve essere normalizzato
    vec3 forward = this->cam.orientation;
    forward.normalize();

    // 2. Right è il prodotto vettoriale tra forward e world_up
    vec3 right = math::cross(forward, world_up);
    right.normalize();

    // 3. Up reale della camera è il prodotto vettoriale tra right e forward
    vec3 up = math::cross(forward, right);
    up.normalize();

    vec3 ray_dir_world = (right * px) + (up * py) + (forward * 1.0f); // Se forward guarda avanti (+Z)
    ray_dir_world.normalize();

    return ray_dir_world;

}