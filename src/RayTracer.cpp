#include <algorithm>
#include <iostream>

#include "headers/RayTracer.h"
#include "headers/Ray.h"
#include "headers/math.h"
#include "headers/mat3.h"

void RayTracer::trace() {
    //if (this->frame > 0) return;

    // Loop over every pixel
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {

            // Trace single ray
            this->pixels.at(i * width + j) = this->trace_ray(
                // Init ray from camera position and orientation
                Ray(
                    this->cam->position,
                    this->getRayDirection(j, i)
                ),
                0
            );
        }
    }
    // Update frame counter
    this->frame++;
}

vec3 RayTracer::trace_ray(Ray ray, int depth) {
    if (depth >= this->bounces) return vec3(-1.0f);

    vec3 color = vec3(-1.0f);
    for (int i=0;i<this->rays_per_pixel;i++) {

        // Loop through every object in the scene and check intersection
        for (auto& obj : this->scene->objects) {
            
            // TODO: support both specular and diffuse

            // TODO: calculate new ray direction based on collision normal vec

            vec3 hit_pos = vec3(0.0f);
            if (ray.intersects(obj, hit_pos)) {
                // New direction, specular reflection
                vec3 normal = obj.normal(hit_pos);
                vec3 new_ray_dir = ray.dir - normal * math::dot(ray.dir, normal) * 2;

                color = obj.color;
                color = color + this->trace_ray(Ray(hit_pos + (normal * 0.01f), new_ray_dir), depth + 1);
            }
        }
    }

    return color;
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
    float aspect_ratio = static_cast<float>(width) / height;

    float fov = 72.0f * 3.14 / 180.0f;
    float scale = std::tan(fov * 0.5f);

    float px = (2.0f * ((x + 0.5f) / width) - 1.0f)
            * aspect_ratio * scale;

    float py = (1.0f - 2.0f * ((y + 0.5f) / height))
            * scale;

    vec3 world_up(0.0f, 1.0f, 0.0f);

    vec3 forward = this->cam->orientation;
    forward.normalize();

    vec3 right = math::cross(forward, world_up);
    right.normalize();

    vec3 up = math::cross(forward, right);
    up.normalize();

    vec3 ray_dir_world =
        right * px +
        up * py +
        forward;

    ray_dir_world.normalize();

    return ray_dir_world;
}