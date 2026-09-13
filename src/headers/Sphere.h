#pragma once

#include "headers/vec3.h"

class Sphere
{
private:

public:

    vec3 center;
    float radius;
    vec3 color;

    Sphere(vec3 center, float radius, vec3 color = vec3(1.0f)) : center(center), radius(radius), color(color) {};

    vec3 normal(vec3 collision) const {

        vec3 normal = collision - this->center;
        normal.normalize();

        return normal;
    }
};

