#include "headers/math.h"
#include "headers/Camera.h"

#include <algorithm>

void Camera::update(float dx, float dy)
{
    yaw += dx;
    pitch += dy;

    pitch = std::clamp(pitch, -89.0f, 89.0f);

    orientation = vec3(
        std::cos(pitch) * std::sin(yaw),
        std::sin(pitch),
        -std::cos(pitch) * std::cos(yaw)
    );

    orientation.normalize();
}