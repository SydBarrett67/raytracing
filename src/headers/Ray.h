#pragma once

#include "vec3.h"

class Ray {
public:

    vec3 origin;
    vec3 dir;

    // Consutrctor
    Ray(vec3 origin, vec3 dir) : origin(origin), dir(dir) {};
};