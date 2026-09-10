#pragma once

#include "headers/vec3.h"
#include "headers/mat3.h"

class Camera
{
private:

    vec3 position;
    vec3 orientation;

public:
    Camera(vec3 position = vec3(0.0f), vec3 orientation = vec3(1.0f, 0.0f, 0.0f))
    : position(position), orientation(orientation) {};

    void update(mat3 transformation_matrix);
};
