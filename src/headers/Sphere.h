#pragma once

#include "headers/vec3.h"
#include "headers/Ray.h"
#include "headers/Object.h"

class Sphere : public Object
{
private:

public:

    vec3 center;
    float radius;
    vec3 color;
    float emittance;

    Sphere(vec3 center, float radius, vec3 color = vec3(1.0f), float emittance = 0.0f) 
    : center(center),
     radius(radius),
     color(color),
     emittance(emittance)  {};

    // Get normal vector from collision point (vec3)
    vec3 normal(vec3 collision) override {

        vec3 normal = collision - this->center;
        normal.normalize();

        return normal;
    };

    vec3 getColor() override {
        return this->color;
    };

    float getEmittance() override {
        return this->emittance;
    };

    // Intersection override
    bool intersects(Ray ray, vec3 &hit_pos, float &distance) override {
        vec3 oc = ray.origin - this->center;

        float a = math::dot(ray.dir, ray.dir);
        float b = 2.0f * math::dot(oc, ray.dir);
        float c = math::dot(oc, oc) - this->radius * this->radius;

        float discriminant = b * b - 4.0f * a * c;

        // Missed, early return
        if (discriminant < 0.0f) 
        {
            return false;
        }

        float sqrt_disc = std::sqrt(discriminant);
        float t = (-b - sqrt_disc) / (2.0f * a);

        if (t < 0.0f) {
            t = (-b + sqrt_disc) / (2.0f * a);
        }
        if (t < 0.0f) {
            return false;
        }

        distance = t;

        hit_pos = ray.origin + (ray.dir * t);

        return true;
    };
};