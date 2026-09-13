#pragma once

#include "vec3.h"
#include "headers/Sphere.h"

class Ray {
public:

    vec3 origin;
    vec3 dir;

    // Consutrctor
    Ray(vec3 origin, vec3 dir) : origin(origin), dir(dir) {};

    bool intersects(Sphere obj, vec3 &hit_pos);

};