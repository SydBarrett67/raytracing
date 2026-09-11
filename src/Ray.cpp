#include "headers/Ray.h"
#include "headers/Sphere.h"
#include "headers/vec3.h"

#include "headers/math.h"

bool Ray::intersects(Sphere sphere)
{
    vec3 oc = origin - sphere.center;

    float a = math::dot(dir, dir);
    float b = 2.0f * math::dot(oc, dir);
    float c = math::dot(oc, oc) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4.0f * a * c;

    return discriminant >= 0.0f;
}