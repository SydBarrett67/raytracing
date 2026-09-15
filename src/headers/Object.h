#pragma once

#include "headers/vec3.h"
#include "headers/Ray.h"

// Base class for raytraced objects
class Object
{
public:
    // Mesh constructor
    Object() = default;

    // Get normal vector from collision point (vec3)
    virtual vec3 normal(vec3 collision) = 0;

    // Intersection
    virtual bool intersects(Ray ray, vec3 &hit_pos, float &distance) = 0;

    // Color
    virtual vec3 getColor() = 0;

    // Emittance
    virtual float getEmittance() = 0;

    virtual ~Object() = default;
};

