#pragma once

#include "headers/vec3.h"

class Sphere
{
private:

public:

    vec3 center;
    float radius;

    Sphere(vec3 center, float radius) : center(center), radius(radius) {};
};

