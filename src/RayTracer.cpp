#include <algorithm>
#include <iostream>

#include "headers/RayTracer.h"
#include "headers/Ray.h"
#include "headers/math.h"
#include "headers/mat3.h"
#include "headers/Sphere.h"

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
    if (depth >= this->bounces) return vec3(0.0f);

    // 1. Corretto il tipo di vettore per memorizzare i puntatori alle luci
    std::vector<Object*> lights;

    vec3 color = vec3(0.0f);
    float distance = 0.0f;

    Object* closest_obj = nullptr;
    vec3 closest_hit_pos = vec3(0.0f);
    float closest_distance = 1e30f; // Inf

    // Loop through every object in the scene and check intersection
    for (auto& obj : this->scene->objects) {
        
        // TODO: support both specular and diffuse

        // 1. Corretto il push_back usando .get() per i puntatori
        if (obj->getEmittance() > 0.0f) lights.push_back(obj.get());

        vec3 hit_pos = vec3(0.0f);

        if (obj->intersects(ray, hit_pos, distance)) {
            if (distance > 0.001f && distance < closest_distance) {
                closest_distance = distance;
                closest_hit_pos = hit_pos;
                closest_obj = obj.get();
            }
        }
    }

    // Calculate reflection on closest obj only
    if (closest_obj != nullptr) {
        // New direction, specular reflection
        vec3 normal = closest_obj->normal(closest_hit_pos);
        vec3 new_ray_dir = ray.dir - normal * math::dot(ray.dir, normal) * 2;

        color = closest_obj->getColor() + closest_obj->getEmittance();
        color = color + this->trace_ray(Ray(closest_hit_pos + (normal * 0.01f), new_ray_dir), depth + 1);

        // Shadow loop
        for (Object* light_obj : lights) {
            
            // Light center
            Sphere* light_sphere = static_cast<Sphere*>(light_obj);
            vec3 light_dir = light_sphere->center - closest_hit_pos;

            float distance_to_light = std::sqrt(math::dot(light_dir, light_dir));
            light_dir.normalize();

            Ray shadow_ray = Ray(closest_hit_pos + (normal * 0.01f), light_dir);
            float shadow_dist = 0.0f;

            for (auto& obj : this->scene->objects) {
                // Skip itself
                if (obj.get() == light_obj) continue; 

                vec3 shadow_hit_pos = vec3(0.0f);
                if (obj->intersects(shadow_ray, shadow_hit_pos, shadow_dist)) {
                    if (shadow_dist > 0.001f && shadow_dist < distance_to_light) {
                        color = color * 0.2f;
                        break; // In shadow
                    }
                }
            }
        }
    }
    else {
        color = vec3(0.0f); 
    }

    return color;
}



std::vector<uint8_t> RayTracer::getPixels()
{
    std::vector<uint8_t> bytes;
    bytes.reserve(width * height * 4);

    for (const auto& px : pixels) {
        float r_mapped = px.x / (px.x + 1.0f);
        float g_mapped = px.y / (px.y + 1.0f);
        float b_mapped = px.z / (px.z + 1.0f);

        // Ora converti in byte (0-255)
        uint8_t r = static_cast<uint8_t>(std::clamp(r_mapped * 255.0f, 0.0f, 255.0f));
        uint8_t g = static_cast<uint8_t>(std::clamp(g_mapped * 255.0f, 0.0f, 255.0f));
        uint8_t b = static_cast<uint8_t>(std::clamp(b_mapped * 255.0f, 0.0f, 255.0f));

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

    float fov = 90.0f * 3.14 / 180.0f;
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