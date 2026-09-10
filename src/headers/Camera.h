#include "headers/vec3.h"

class Camera
{
private:

    vec3 position;
    vec3 orientation;

public:
    Camera(vec3 position, vec3 orientation = vec3(0.0f))
    : position(position), orientation(orientation) {};

    
};
